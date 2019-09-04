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
struct pci_dev {int dummy; } ;
struct apertures_struct {TYPE_1__* ranges; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 struct apertures_struct* alloc_apertures (int) ; 
 int /*<<< orphan*/  kfree (struct apertures_struct*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_conflicting_framebuffers (struct apertures_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int radeon_kick_out_firmware_fb(struct pci_dev *pdev)
{
	struct apertures_struct *ap;

	ap = alloc_apertures(1);
	if (!ap)
		return -ENOMEM;

	ap->ranges[0].base = pci_resource_start(pdev, 0);
	ap->ranges[0].size = pci_resource_len(pdev, 0);

	remove_conflicting_framebuffers(ap, KBUILD_MODNAME, false);

	kfree(ap);

	return 0;
}