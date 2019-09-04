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
struct TYPE_4__ {int /*<<< orphan*/  fis; } ;
struct domain_device {TYPE_2__ sata_dev; } ;
struct ata_queued_cmd {int /*<<< orphan*/  result_tf; TYPE_1__* ap; } ;
struct TYPE_3__ {struct domain_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_tf_from_fis (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sas_ata_qc_fill_rtf(struct ata_queued_cmd *qc)
{
	struct domain_device *dev = qc->ap->private_data;

	ata_tf_from_fis(dev->sata_dev.fis, &qc->result_tf);
	return true;
}