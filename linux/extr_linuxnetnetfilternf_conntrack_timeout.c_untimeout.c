#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nf_conn_timeout {void* timeout; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (void*,int /*<<< orphan*/ *) ; 
 struct nf_conn_timeout* nf_ct_timeout_find (struct nf_conn*) ; 

__attribute__((used)) static int untimeout(struct nf_conn *ct, void *timeout)
{
	struct nf_conn_timeout *timeout_ext = nf_ct_timeout_find(ct);

	if (timeout_ext && (!timeout || timeout_ext->timeout == timeout))
		RCU_INIT_POINTER(timeout_ext->timeout, NULL);

	/* We are not intended to delete this conntrack. */
	return 0;
}