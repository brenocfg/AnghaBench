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
typedef  scalar_t__ u8 ;
struct us_data {scalar_t__ extra; scalar_t__ iobuf; } ;
struct SD_STATUS {scalar_t__ WtP; scalar_t__ HiSpeed; scalar_t__ HiCapacity; scalar_t__ IsMMC; scalar_t__ Ready; scalar_t__ Insert; } ;
struct ene_ub6250_info {struct SD_STATUS SD_Status; scalar_t__* bbuf; } ;
struct bulk_cb_wrap {int* CDB; int DataTransferLength; void* Flags; void* Signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDIR_READ ; 
 int /*<<< orphan*/  SD_INIT1_PATTERN ; 
 int /*<<< orphan*/  SD_INIT2_PATTERN ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_BULK_CB_SIGN ; 
 void* US_BULK_FLAG_IN ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_get_card_status (struct us_data*,scalar_t__*) ; 
 int ene_load_bincode (struct us_data*,int /*<<< orphan*/ ) ; 
 int ene_send_scsi_cmd (struct us_data*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bulk_cb_wrap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static int ene_sd_init(struct us_data *us)
{
	int result;
	struct bulk_cb_wrap *bcb = (struct bulk_cb_wrap *) us->iobuf;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;

	usb_stor_dbg(us, "transport --- ENE_SDInit\n");
	/* SD Init Part-1 */
	result = ene_load_bincode(us, SD_INIT1_PATTERN);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Load SD Init Code Part-1 Fail !!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}

	memset(bcb, 0, sizeof(struct bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->Flags = US_BULK_FLAG_IN;
	bcb->CDB[0] = 0xF2;

	result = ene_send_scsi_cmd(us, FDIR_READ, NULL, 0);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Execution SD Init Code Fail !!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}

	/* SD Init Part-2 */
	result = ene_load_bincode(us, SD_INIT2_PATTERN);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Load SD Init Code Part-2 Fail !!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}

	memset(bcb, 0, sizeof(struct bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200;
	bcb->Flags              = US_BULK_FLAG_IN;
	bcb->CDB[0]             = 0xF1;

	result = ene_send_scsi_cmd(us, FDIR_READ, bbuf, 0);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Execution SD Init Code Fail !!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}

	info->SD_Status =  *(struct SD_STATUS *) bbuf;
	if (info->SD_Status.Insert && info->SD_Status.Ready) {
		struct SD_STATUS *s = &info->SD_Status;

		ene_get_card_status(us, bbuf);
		usb_stor_dbg(us, "Insert     = %x\n", s->Insert);
		usb_stor_dbg(us, "Ready      = %x\n", s->Ready);
		usb_stor_dbg(us, "IsMMC      = %x\n", s->IsMMC);
		usb_stor_dbg(us, "HiCapacity = %x\n", s->HiCapacity);
		usb_stor_dbg(us, "HiSpeed    = %x\n", s->HiSpeed);
		usb_stor_dbg(us, "WtP        = %x\n", s->WtP);
	} else {
		usb_stor_dbg(us, "SD Card Not Ready --- %x\n", bbuf[0]);
		return USB_STOR_TRANSPORT_ERROR;
	}
	return USB_STOR_TRANSPORT_GOOD;
}