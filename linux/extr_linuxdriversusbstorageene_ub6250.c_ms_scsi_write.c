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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct us_data {scalar_t__ extra; scalar_t__ iobuf; } ;
struct scsi_cmnd {unsigned char* cmnd; } ;
struct TYPE_4__ {int PagesPerBlock; int /*<<< orphan*/ * Phy2LogMap; } ;
struct TYPE_3__ {scalar_t__ IsMSPro; } ;
struct ene_ub6250_info {int bl_num; TYPE_2__ MS_Lib; TYPE_1__ MS_Status; } ;
struct bulk_cb_wrap {int DataTransferLength; int Flags; int* CDB; int /*<<< orphan*/  Signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDIR_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSP_RW_PATTERN ; 
 int MS_BYTES_PER_PAGE ; 
 int /*<<< orphan*/  MS_LB_NOT_USED_ERASED ; 
 int /*<<< orphan*/  MS_RW_PATTERN ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_BULK_CB_SIGN ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ene_load_bincode (struct us_data*,int /*<<< orphan*/ ) ; 
 int ene_send_scsi_cmd (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bulk_cb_wrap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ms_lib_force_setlogical_pair (struct us_data*,int,int) ; 
 int ms_libconv_to_physical (struct ene_ub6250_info*,int) ; 
 int ms_libsearch_block_from_logical (struct us_data*,int) ; 
 int ms_read_copyblock (struct us_data*,int,int,int,int,void*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  usb_stor_set_xfer_buf (void*,int,struct scsi_cmnd*) ; 

__attribute__((used)) static int ms_scsi_write(struct us_data *us, struct scsi_cmnd *srb)
{
	int result;
	struct bulk_cb_wrap *bcb = (struct bulk_cb_wrap *) us->iobuf;
	unsigned char *cdb = srb->cmnd;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	u32 bn = ((cdb[2] << 24) & 0xff000000) |
			((cdb[3] << 16) & 0x00ff0000) |
			((cdb[4] << 8) & 0x0000ff00) |
			((cdb[5] << 0) & 0x000000ff);
	u16 blen = ((cdb[7] << 8) & 0xff00) | ((cdb[8] << 0) & 0x00ff);
	u32 blenByte = blen * 0x200;

	if (bn > info->bl_num)
		return USB_STOR_TRANSPORT_ERROR;

	if (info->MS_Status.IsMSPro) {
		result = ene_load_bincode(us, MSP_RW_PATTERN);
		if (result != USB_STOR_XFER_GOOD) {
			pr_info("Load MSP RW pattern Fail !!\n");
			return USB_STOR_TRANSPORT_ERROR;
		}

		/* set up the command wrapper */
		memset(bcb, 0, sizeof(struct bulk_cb_wrap));
		bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
		bcb->DataTransferLength = blenByte;
		bcb->Flags  = 0x00;
		bcb->CDB[0] = 0xF0;
		bcb->CDB[1] = 0x04;
		bcb->CDB[5] = (unsigned char)(bn);
		bcb->CDB[4] = (unsigned char)(bn>>8);
		bcb->CDB[3] = (unsigned char)(bn>>16);
		bcb->CDB[2] = (unsigned char)(bn>>24);

		result = ene_send_scsi_cmd(us, FDIR_WRITE, scsi_sglist(srb), 1);
	} else {
		void *buf;
		int offset = 0;
		u16 PhyBlockAddr;
		u8 PageNum;
		u16 len, oldphy, newphy;

		buf = kmalloc(blenByte, GFP_KERNEL);
		if (buf == NULL)
			return USB_STOR_TRANSPORT_ERROR;
		usb_stor_set_xfer_buf(buf, blenByte, srb);

		result = ene_load_bincode(us, MS_RW_PATTERN);
		if (result != USB_STOR_XFER_GOOD) {
			pr_info("Load MS RW pattern Fail !!\n");
			result = USB_STOR_TRANSPORT_ERROR;
			goto exit;
		}

		PhyBlockAddr = (u16)(bn / info->MS_Lib.PagesPerBlock);
		PageNum      = (u8)(bn % info->MS_Lib.PagesPerBlock);

		while (1) {
			if (blen > (info->MS_Lib.PagesPerBlock-PageNum))
				len = info->MS_Lib.PagesPerBlock-PageNum;
			else
				len = blen;

			oldphy = ms_libconv_to_physical(info, PhyBlockAddr); /* need check us <-> info */
			newphy = ms_libsearch_block_from_logical(us, PhyBlockAddr);

			result = ms_read_copyblock(us, oldphy, newphy, PhyBlockAddr, PageNum, buf+offset, len);

			if (result != USB_STOR_XFER_GOOD) {
				pr_info("MS_SCSI_Write --- result = %x\n", result);
				result =  USB_STOR_TRANSPORT_ERROR;
				goto exit;
			}

			info->MS_Lib.Phy2LogMap[oldphy] = MS_LB_NOT_USED_ERASED;
			ms_lib_force_setlogical_pair(us, PhyBlockAddr, newphy);

			blen -= len;
			if (blen <= 0)
				break;
			PhyBlockAddr++;
			PageNum = 0;
			offset += MS_BYTES_PER_PAGE*len;
		}
exit:
		kfree(buf);
	}
	return result;
}