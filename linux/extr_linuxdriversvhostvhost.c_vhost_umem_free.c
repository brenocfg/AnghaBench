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
struct vhost_umem_node {int /*<<< orphan*/  link; } ;
struct vhost_umem {int /*<<< orphan*/  numem; int /*<<< orphan*/  umem_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vhost_umem_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_umem_interval_tree_remove (struct vhost_umem_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_umem_free(struct vhost_umem *umem,
			    struct vhost_umem_node *node)
{
	vhost_umem_interval_tree_remove(node, &umem->umem_tree);
	list_del(&node->link);
	kfree(node);
	umem->numem--;
}