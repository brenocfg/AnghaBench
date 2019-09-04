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
struct td_node {int /*<<< orphan*/  dma; int /*<<< orphan*/  ptr; } ;
struct ci_hw_ep {struct td_node* pending_td; int /*<<< orphan*/  td_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct td_node*) ; 

__attribute__((used)) static void free_pending_td(struct ci_hw_ep *hwep)
{
	struct td_node *pending = hwep->pending_td;

	dma_pool_free(hwep->td_pool, pending->ptr, pending->dma);
	hwep->pending_td = NULL;
	kfree(pending);
}