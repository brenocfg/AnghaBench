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
struct us_data {scalar_t__ extra; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_2__ {scalar_t__ WtP; } ;
struct ene_ub6250_info {TYPE_1__ SD_Status; } ;

/* Variables and functions */
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  usb_stor_set_xfer_buf (unsigned char*,int,struct scsi_cmnd*) ; 

__attribute__((used)) static int sd_scsi_mode_sense(struct us_data *us, struct scsi_cmnd *srb)
{
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;
	unsigned char mediaNoWP[12] = {
		0x0b, 0x00, 0x00, 0x08, 0x00, 0x00,
		0x71, 0xc0, 0x00, 0x00, 0x02, 0x00 };
	unsigned char mediaWP[12]   = {
		0x0b, 0x00, 0x80, 0x08, 0x00, 0x00,
		0x71, 0xc0, 0x00, 0x00, 0x02, 0x00 };

	if (info->SD_Status.WtP)
		usb_stor_set_xfer_buf(mediaWP, 12, srb);
	else
		usb_stor_set_xfer_buf(mediaNoWP, 12, srb);


	return USB_STOR_TRANSPORT_GOOD;
}