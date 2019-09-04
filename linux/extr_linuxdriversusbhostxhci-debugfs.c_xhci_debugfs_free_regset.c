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
struct xhci_regset {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct xhci_regset*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xhci_debugfs_free_regset(struct xhci_regset *regset)
{
	if (!regset)
		return;

	list_del(&regset->list);
	kfree(regset);
}