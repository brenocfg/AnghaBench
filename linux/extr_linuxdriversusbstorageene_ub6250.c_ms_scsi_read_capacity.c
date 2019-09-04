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
typedef  int u32 ;
typedef  int u16 ;
struct us_data {scalar_t__ extra; } ;
struct scsi_cmnd {int dummy; } ;
struct scatterlist {int dummy; } ;
struct TYPE_4__ {int NumberOfLogBlock; int blockSize; } ;
struct TYPE_3__ {scalar_t__ IsMSPro; } ;
struct ene_ub6250_info {int MSP_TotalBlock; int bl_num; TYPE_2__ MS_Lib; TYPE_1__ MS_Status; } ;

/* Variables and functions */
 int /*<<< orphan*/  TO_XFER_BUF ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  usb_stor_access_xfer_buf (unsigned char*,int,struct scsi_cmnd*,struct scatterlist**,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static int ms_scsi_read_capacity(struct us_data *us, struct scsi_cmnd *srb)
{
	u32   bl_num;
	u16    bl_len;
	unsigned int offset = 0;
	unsigned char    buf[8];
	struct scatterlist *sg = NULL;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	usb_stor_dbg(us, "ms_scsi_read_capacity\n");
	bl_len = 0x200;
	if (info->MS_Status.IsMSPro)
		bl_num = info->MSP_TotalBlock - 1;
	else
		bl_num = info->MS_Lib.NumberOfLogBlock * info->MS_Lib.blockSize * 2 - 1;

	info->bl_num = bl_num;
	usb_stor_dbg(us, "bl_len = %x\n", bl_len);
	usb_stor_dbg(us, "bl_num = %x\n", bl_num);

	/*srb->request_bufflen = 8; */
	buf[0] = (bl_num >> 24) & 0xff;
	buf[1] = (bl_num >> 16) & 0xff;
	buf[2] = (bl_num >> 8) & 0xff;
	buf[3] = (bl_num >> 0) & 0xff;
	buf[4] = (bl_len >> 24) & 0xff;
	buf[5] = (bl_len >> 16) & 0xff;
	buf[6] = (bl_len >> 8) & 0xff;
	buf[7] = (bl_len >> 0) & 0xff;

	usb_stor_access_xfer_buf(buf, 8, srb, &sg, &offset, TO_XFER_BUF);

	return USB_STOR_TRANSPORT_GOOD;
}