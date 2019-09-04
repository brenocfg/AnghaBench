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
typedef  int /*<<< orphan*/  u32 ;
struct rocker_wait {int dummy; } ;
struct rocker {struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  TEST_DMA_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  rocker_wait_event_timeout (struct rocker_wait*,int) ; 
 int /*<<< orphan*/  rocker_wait_reset (struct rocker_wait*) ; 
 int /*<<< orphan*/  rocker_write32 (struct rocker const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_dma_test_one(const struct rocker *rocker,
			       struct rocker_wait *wait, u32 test_type,
			       dma_addr_t dma_handle, const unsigned char *buf,
			       const unsigned char *expect, size_t size)
{
	const struct pci_dev *pdev = rocker->pdev;
	int i;

	rocker_wait_reset(wait);
	rocker_write32(rocker, TEST_DMA_CTRL, test_type);

	if (!rocker_wait_event_timeout(wait, HZ / 10)) {
		dev_err(&pdev->dev, "no interrupt received within a timeout\n");
		return -EIO;
	}

	for (i = 0; i < size; i++) {
		if (buf[i] != expect[i]) {
			dev_err(&pdev->dev, "unexpected memory content %02x at byte %x\n, %02x expected",
				buf[i], i, expect[i]);
			return -EIO;
		}
	}
	return 0;
}