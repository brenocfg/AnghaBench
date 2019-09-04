#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_2__ {struct sock** sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ pnres ; 
 int /*<<< orphan*/  resource_mutex ; 

void pn_sock_unbind_all_res(struct sock *sk)
{
	unsigned int res, match = 0;

	mutex_lock(&resource_mutex);
	for (res = 0; res < 256; res++) {
		if (pnres.sk[res] == sk) {
			RCU_INIT_POINTER(pnres.sk[res], NULL);
			match++;
		}
	}
	mutex_unlock(&resource_mutex);

	while (match > 0) {
		__sock_put(sk);
		match--;
	}
	/* Caller is responsible for RCU sync before final sock_put() */
}