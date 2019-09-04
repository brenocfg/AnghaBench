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
struct ata_taskfile {int /*<<< orphan*/  command; int /*<<< orphan*/  ctl; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_DEV_RESET ; 
 int /*<<< orphan*/  ATA_SRST ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 
 int /*<<< orphan*/  ata_tf_to_fis (struct ata_taskfile*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_sas_fill_ata_reset_cmd(struct ata_device *dev,
		bool reset, int pmp, u8 *fis)
{
	struct ata_taskfile tf;

	ata_tf_init(dev, &tf);
	if (reset)
		tf.ctl |= ATA_SRST;
	else
		tf.ctl &= ~ATA_SRST;
	tf.command = ATA_CMD_DEV_RESET;
	ata_tf_to_fis(&tf, pmp, 0, fis);
}