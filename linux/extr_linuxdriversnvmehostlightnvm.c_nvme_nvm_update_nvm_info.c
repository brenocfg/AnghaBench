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
struct nvme_ns {int lba_shift; int /*<<< orphan*/  ms; struct nvm_dev* ndev; } ;
struct nvm_geo {int csecs; int /*<<< orphan*/  sos; } ;
struct nvm_dev {struct nvm_geo geo; } ;

/* Variables and functions */

void nvme_nvm_update_nvm_info(struct nvme_ns *ns)
{
	struct nvm_dev *ndev = ns->ndev;
	struct nvm_geo *geo = &ndev->geo;

	geo->csecs = 1 << ns->lba_shift;
	geo->sos = ns->ms;
}