#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_2__* vpd; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write ) (struct pci_dev*,int /*<<< orphan*/ ,size_t,void const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*,int /*<<< orphan*/ ,size_t,void const*) ; 

ssize_t pci_write_vpd(struct pci_dev *dev, loff_t pos, size_t count, const void *buf)
{
	if (!dev->vpd || !dev->vpd->ops)
		return -ENODEV;
	return dev->vpd->ops->write(dev, pos, count, buf);
}