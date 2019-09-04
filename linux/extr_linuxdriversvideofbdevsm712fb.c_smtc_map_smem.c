#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct smtcfb_info {TYPE_3__* fb; int /*<<< orphan*/  lfb; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct TYPE_4__ {int bits_per_pixel; } ;
struct TYPE_6__ {TYPE_2__ fix; int /*<<< orphan*/  screen_base; TYPE_1__ var; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ big_addr ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smtc_map_smem(struct smtcfb_info *sfb,
			 struct pci_dev *pdev, u_long smem_len)
{
	sfb->fb->fix.smem_start = pci_resource_start(pdev, 0);

	if (sfb->fb->var.bits_per_pixel == 32)
		sfb->fb->fix.smem_start += big_addr;

	sfb->fb->fix.smem_len = smem_len;

	sfb->fb->screen_base = sfb->lfb;

	if (!sfb->fb->screen_base) {
		dev_err(&pdev->dev,
			"%s: unable to map screen memory\n", sfb->fb->fix.id);
		return -ENOMEM;
	}

	return 0;
}