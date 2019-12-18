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
typedef  size_t u8 ;
struct sock {int dummy; } ;
struct TYPE_2__ {struct sock** sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ pnres ; 
 int /*<<< orphan*/  resource_mutex ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

int pn_sock_unbind_res(struct sock *sk, u8 res)
{
	int ret = -ENOENT;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	mutex_lock(&resource_mutex);
	if (pnres.sk[res] == sk) {
		RCU_INIT_POINTER(pnres.sk[res], NULL);
		ret = 0;
	}
	mutex_unlock(&resource_mutex);

	if (ret == 0) {
		synchronize_rcu();
		sock_put(sk);
	}
	return ret;
}