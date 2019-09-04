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
struct rocker_wait {int dummy; } ;
struct rocker {struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  ROCKER_MSIX_VEC_TEST ; 
 int /*<<< orphan*/  TEST_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rocker_wait*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rocker_wait*) ; 
 int rocker_dma_test (struct rocker const*,struct rocker_wait*) ; 
 int /*<<< orphan*/  rocker_driver_name ; 
 int /*<<< orphan*/  rocker_msix_vector (struct rocker const*,int /*<<< orphan*/ ) ; 
 int rocker_reg_test (struct rocker const*) ; 
 int /*<<< orphan*/  rocker_test_irq_handler ; 
 int /*<<< orphan*/  rocker_wait_event_timeout (struct rocker_wait*,int) ; 
 int /*<<< orphan*/  rocker_wait_init (struct rocker_wait*) ; 
 int /*<<< orphan*/  rocker_write32 (struct rocker const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_basic_hw_test(const struct rocker *rocker)
{
	const struct pci_dev *pdev = rocker->pdev;
	struct rocker_wait wait;
	int err;

	err = rocker_reg_test(rocker);
	if (err) {
		dev_err(&pdev->dev, "reg test failed\n");
		return err;
	}

	err = request_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_TEST),
			  rocker_test_irq_handler, 0,
			  rocker_driver_name, &wait);
	if (err) {
		dev_err(&pdev->dev, "cannot assign test irq\n");
		return err;
	}

	rocker_wait_init(&wait);
	rocker_write32(rocker, TEST_IRQ, ROCKER_MSIX_VEC_TEST);

	if (!rocker_wait_event_timeout(&wait, HZ / 10)) {
		dev_err(&pdev->dev, "no interrupt received within a timeout\n");
		err = -EIO;
		goto free_irq;
	}

	err = rocker_dma_test(rocker, &wait);
	if (err)
		dev_err(&pdev->dev, "dma test failed\n");

free_irq:
	free_irq(rocker_msix_vector(rocker, ROCKER_MSIX_VEC_TEST), &wait);
	return err;
}