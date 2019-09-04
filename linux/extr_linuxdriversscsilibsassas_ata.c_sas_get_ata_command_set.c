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
typedef  int /*<<< orphan*/  u8 ;
struct domain_device {scalar_t__ dev_type; scalar_t__ frame_rcvd; } ;
struct dev_to_host_fis {int dummy; } ;
struct ata_taskfile {int dummy; } ;

/* Variables and functions */
 int ATA_DEV_UNKNOWN ; 
 scalar_t__ SAS_SATA_PENDING ; 
 int ata_dev_classify (struct ata_taskfile*) ; 
 int /*<<< orphan*/  ata_tf_from_fis (int /*<<< orphan*/  const*,struct ata_taskfile*) ; 

__attribute__((used)) static int sas_get_ata_command_set(struct domain_device *dev)
{
	struct dev_to_host_fis *fis =
		(struct dev_to_host_fis *) dev->frame_rcvd;
	struct ata_taskfile tf;

	if (dev->dev_type == SAS_SATA_PENDING)
		return ATA_DEV_UNKNOWN;

	ata_tf_from_fis((const u8 *)fis, &tf);

	return ata_dev_classify(&tf);
}