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
struct scsi_cmnd {int dummy; } ;
typedef  int /*<<< orphan*/  inq_data ;

/* Variables and functions */
 char TYPE_DISK ; 
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (struct scsi_cmnd*,char*,int) ; 
 int /*<<< orphan*/  scsi_sg_copy_to_buffer (struct scsi_cmnd*,char*,int) ; 

__attribute__((used)) static void aac_expose_phy_device(struct scsi_cmnd *scsicmd)
{
	char inq_data;
	scsi_sg_copy_to_buffer(scsicmd,  &inq_data, sizeof(inq_data));
	if ((inq_data & 0x20) && (inq_data & 0x1f) == TYPE_DISK) {
		inq_data &= 0xdf;
		scsi_sg_copy_from_buffer(scsicmd, &inq_data, sizeof(inq_data));
	}
}