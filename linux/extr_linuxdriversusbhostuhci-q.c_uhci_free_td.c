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
struct uhci_td {int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  fl_list; int /*<<< orphan*/  list; } ;
struct uhci_hcd {int /*<<< orphan*/  td_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*,struct uhci_td*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct uhci_td*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhci_dev (struct uhci_hcd*) ; 

__attribute__((used)) static void uhci_free_td(struct uhci_hcd *uhci, struct uhci_td *td)
{
	if (!list_empty(&td->list))
		dev_WARN(uhci_dev(uhci), "td %p still in list!\n", td);
	if (!list_empty(&td->fl_list))
		dev_WARN(uhci_dev(uhci), "td %p still in fl_list!\n", td);

	dma_pool_free(uhci->td_pool, td, td->dma_handle);
}