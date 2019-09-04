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
struct pci_platform_pm_ops {int /*<<< orphan*/  need_resume; int /*<<< orphan*/  set_wakeup; int /*<<< orphan*/  choose_state; int /*<<< orphan*/  get_state; int /*<<< orphan*/  set_state; int /*<<< orphan*/  is_manageable; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pci_platform_pm_ops const* pci_platform_pm ; 

int pci_set_platform_pm(const struct pci_platform_pm_ops *ops)
{
	if (!ops->is_manageable || !ops->set_state  || !ops->get_state ||
	    !ops->choose_state  || !ops->set_wakeup || !ops->need_resume)
		return -EINVAL;
	pci_platform_pm = ops;
	return 0;
}