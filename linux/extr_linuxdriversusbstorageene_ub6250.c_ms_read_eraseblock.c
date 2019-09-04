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
typedef  int u32 ;
struct us_data {scalar_t__ iobuf; } ;
struct bulk_cb_wrap {int DataTransferLength; int* CDB; int /*<<< orphan*/  Flags; int /*<<< orphan*/  Signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDIR_READ ; 
 int /*<<< orphan*/  MS_RW_PATTERN ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_BULK_CB_SIGN ; 
 int /*<<< orphan*/  US_BULK_FLAG_IN ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ene_load_bincode (struct us_data*,int /*<<< orphan*/ ) ; 
 int ene_send_scsi_cmd (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bulk_cb_wrap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ms_read_eraseblock(struct us_data *us, u32 PhyBlockAddr)
{
	struct bulk_cb_wrap *bcb = (struct bulk_cb_wrap *) us->iobuf;
	int result;
	u32 bn = PhyBlockAddr;

	result = ene_load_bincode(us, MS_RW_PATTERN);
	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	memset(bcb, 0, sizeof(struct bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200;
	bcb->Flags = US_BULK_FLAG_IN;
	bcb->CDB[0] = 0xF2;
	bcb->CDB[1] = 0x06;
	bcb->CDB[4] = (unsigned char)(bn);
	bcb->CDB[3] = (unsigned char)(bn>>8);
	bcb->CDB[2] = (unsigned char)(bn>>16);

	result = ene_send_scsi_cmd(us, FDIR_READ, NULL, 0);
	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	return USB_STOR_TRANSPORT_GOOD;
}