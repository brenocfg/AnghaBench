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
struct us_data {scalar_t__ extra; } ;
struct scsi_cmnd {int dummy; } ;
struct ene_ub6250_info {int SrbStatus; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_stor_set_xfer_buf (unsigned char*,int,struct scsi_cmnd*) ; 

__attribute__((used)) static int do_scsi_request_sense(struct us_data *us, struct scsi_cmnd *srb)
{
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;
	unsigned char buf[18];

	memset(buf, 0, 18);
	buf[0] = 0x70;				/* Current error */
	buf[2] = info->SrbStatus >> 16;		/* Sense key */
	buf[7] = 10;				/* Additional length */
	buf[12] = info->SrbStatus >> 8;		/* ASC */
	buf[13] = info->SrbStatus;		/* ASCQ */

	usb_stor_set_xfer_buf(buf, sizeof(buf), srb);
	return USB_STOR_TRANSPORT_GOOD;
}