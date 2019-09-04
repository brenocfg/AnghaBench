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
struct nf_conn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void xt_ct_destroy_timeout(struct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTRACK_TIMEOUT
	struct nf_conn_timeout *timeout_ext;
	typeof(nf_ct_timeout_put_hook) timeout_put;

	rcu_read_lock();
	timeout_put = rcu_dereference(nf_ct_timeout_put_hook);

	if (timeout_put) {
		timeout_ext = nf_ct_timeout_find(ct);
		if (timeout_ext) {
			timeout_put(timeout_ext->timeout);
			RCU_INIT_POINTER(timeout_ext->timeout, NULL);
		}
	}
	rcu_read_unlock();
#endif
}