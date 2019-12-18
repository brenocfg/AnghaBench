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
struct qlist_node {int dummy; } ;
struct kmem_cache {int dummy; } ;
struct TYPE_2__ {struct kmem_cache* slab_cache; } ;

/* Variables and functions */
 TYPE_1__* virt_to_head_page (struct qlist_node*) ; 

__attribute__((used)) static struct kmem_cache *qlink_to_cache(struct qlist_node *qlink)
{
	return virt_to_head_page(qlink)->slab_cache;
}