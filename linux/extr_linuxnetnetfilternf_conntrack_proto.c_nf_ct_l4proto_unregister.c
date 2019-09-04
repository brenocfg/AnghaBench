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
struct nf_conntrack_l4proto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nf_ct_l4proto_unregister_one (struct nf_conntrack_l4proto const* const) ; 
 int /*<<< orphan*/  kill_l4proto ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_iterate_destroy (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nf_ct_proto_mutex ; 
 int /*<<< orphan*/  synchronize_net () ; 

__attribute__((used)) static void
nf_ct_l4proto_unregister(const struct nf_conntrack_l4proto * const l4proto[],
			 unsigned int num_proto)
{
	int i;

	mutex_lock(&nf_ct_proto_mutex);
	for (i = 0; i < num_proto; i++)
		__nf_ct_l4proto_unregister_one(l4proto[i]);
	mutex_unlock(&nf_ct_proto_mutex);

	synchronize_net();

	for (i = 0; i < num_proto; i++)
		nf_ct_iterate_destroy(kill_l4proto, (void *)l4proto[i]);
}