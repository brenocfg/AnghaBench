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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct csio_lnode {int /*<<< orphan*/  portid; } ;
struct csio_hw {int num_pports; int /*<<< orphan*/  lock; TYPE_1__* pport; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  csio_hw_free (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_stop (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_lnode_init_post (struct csio_lnode*) ; 
 scalar_t__ csio_lnode_start (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lnodes_block_request (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_lnodes_exit (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_lnodes_unblock_request (struct csio_hw*) ; 
 struct csio_lnode* csio_shost_init (struct csio_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct csio_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_pci_resume(struct pci_dev *pdev)
{
	struct csio_hw *hw = pci_get_drvdata(pdev);
	struct csio_lnode *ln;
	int rv = 0;
	int i;

	/* Bring the LINK UP and Resume IO */

	for (i = 0; i < hw->num_pports; i++) {
		ln = csio_shost_init(hw, &pdev->dev, true, NULL);
		if (!ln) {
			rv = -ENODEV;
			break;
		}
		/* Initialize portid */
		ln->portid = hw->pport[i].portid;

		spin_lock_irq(&hw->lock);
		if (csio_lnode_start(ln) != 0)
			rv = -ENODEV;
		spin_unlock_irq(&hw->lock);

		if (rv)
			break;

		csio_lnode_init_post(ln);
	}

	if (rv)
		goto err_resume_exit;

	return;

err_resume_exit:
	csio_lnodes_block_request(hw);
	spin_lock_irq(&hw->lock);
	csio_hw_stop(hw);
	spin_unlock_irq(&hw->lock);
	csio_lnodes_unblock_request(hw);
	csio_lnodes_exit(hw, 0);
	csio_hw_free(hw);
	dev_err(&pdev->dev, "resume of device failed: %d\n", rv);
}