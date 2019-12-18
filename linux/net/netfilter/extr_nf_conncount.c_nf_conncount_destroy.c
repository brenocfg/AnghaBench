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
struct nf_conncount_data {int /*<<< orphan*/ * root; int /*<<< orphan*/  gc_work; } ;
struct net {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nf_conncount_data*) ; 
 int /*<<< orphan*/  nf_ct_netns_put (struct net*,unsigned int) ; 

void nf_conncount_destroy(struct net *net, unsigned int family,
			  struct nf_conncount_data *data)
{
	unsigned int i;

	cancel_work_sync(&data->gc_work);
	nf_ct_netns_put(net, family);

	for (i = 0; i < ARRAY_SIZE(data->root); ++i)
		destroy_tree(&data->root[i]);

	kfree(data);
}