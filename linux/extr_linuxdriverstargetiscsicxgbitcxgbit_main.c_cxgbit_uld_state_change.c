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
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct cxgbit_device {TYPE_1__ lldi; int /*<<< orphan*/  flags; } ;
typedef  enum cxgb4_state { ____Placeholder_cxgb4_state } cxgb4_state ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_STATE_UP ; 
#define  CXGB4_STATE_DETACH 131 
#define  CXGB4_STATE_DOWN 130 
#define  CXGB4_STATE_START_RECOVERY 129 
#define  CXGB4_STATE_UP 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgbit_close_conn (struct cxgbit_device*) ; 
 int /*<<< orphan*/  cxgbit_detach_cdev (struct cxgbit_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxgbit_uld_state_change(void *handle, enum cxgb4_state state)
{
	struct cxgbit_device *cdev = handle;

	switch (state) {
	case CXGB4_STATE_UP:
		set_bit(CDEV_STATE_UP, &cdev->flags);
		pr_info("cdev %s state UP.\n", pci_name(cdev->lldi.pdev));
		break;
	case CXGB4_STATE_START_RECOVERY:
		clear_bit(CDEV_STATE_UP, &cdev->flags);
		cxgbit_close_conn(cdev);
		pr_info("cdev %s state RECOVERY.\n", pci_name(cdev->lldi.pdev));
		break;
	case CXGB4_STATE_DOWN:
		pr_info("cdev %s state DOWN.\n", pci_name(cdev->lldi.pdev));
		break;
	case CXGB4_STATE_DETACH:
		clear_bit(CDEV_STATE_UP, &cdev->flags);
		pr_info("cdev %s state DETACH.\n", pci_name(cdev->lldi.pdev));
		cxgbit_detach_cdev(cdev);
		break;
	default:
		pr_info("cdev %s unknown state %d.\n",
			pci_name(cdev->lldi.pdev), state);
		break;
	}
	return 0;
}