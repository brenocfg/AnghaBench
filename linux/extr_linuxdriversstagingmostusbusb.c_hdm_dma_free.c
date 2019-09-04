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
struct most_dev {int /*<<< orphan*/  usb_device; } ;
struct mbo {int /*<<< orphan*/  bus_address; int /*<<< orphan*/  virt_address; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 struct most_dev* to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdm_dma_free(struct mbo *mbo, u32 size)
{
	struct most_dev *mdev = to_mdev(mbo->ifp);

	usb_free_coherent(mdev->usb_device, size, mbo->virt_address,
			  mbo->bus_address);
}