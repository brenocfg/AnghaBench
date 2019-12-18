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
struct TYPE_2__ {int /*<<< orphan*/  DataCount; int /*<<< orphan*/  TotalDataCount; } ;
struct smb_t2_rsp {TYPE_1__ t2_rsp; } ;
struct smb_hdr {scalar_t__ Command; int WordCount; } ;
typedef  int __u16 ;

/* Variables and functions */
 int CIFSMaxBufSize ; 
 int EINVAL ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ SMB_COM_TRANSACTION2 ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check2ndT2(char *buf)
{
	struct smb_hdr *pSMB = (struct smb_hdr *)buf;
	struct smb_t2_rsp *pSMBt;
	int remaining;
	__u16 total_data_size, data_in_this_rsp;

	if (pSMB->Command != SMB_COM_TRANSACTION2)
		return 0;

	/* check for plausible wct, bcc and t2 data and parm sizes */
	/* check for parm and data offset going beyond end of smb */
	if (pSMB->WordCount != 10) { /* coalesce_t2 depends on this */
		cifs_dbg(FYI, "invalid transact2 word count\n");
		return -EINVAL;
	}

	pSMBt = (struct smb_t2_rsp *)pSMB;

	total_data_size = get_unaligned_le16(&pSMBt->t2_rsp.TotalDataCount);
	data_in_this_rsp = get_unaligned_le16(&pSMBt->t2_rsp.DataCount);

	if (total_data_size == data_in_this_rsp)
		return 0;
	else if (total_data_size < data_in_this_rsp) {
		cifs_dbg(FYI, "total data %d smaller than data in frame %d\n",
			 total_data_size, data_in_this_rsp);
		return -EINVAL;
	}

	remaining = total_data_size - data_in_this_rsp;

	cifs_dbg(FYI, "missing %d bytes from transact2, check next response\n",
		 remaining);
	if (total_data_size > CIFSMaxBufSize) {
		cifs_dbg(VFS, "TotalDataSize %d is over maximum buffer %d\n",
			 total_data_size, CIFSMaxBufSize);
		return -EINVAL;
	}
	return remaining;
}