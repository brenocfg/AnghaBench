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
struct smb2_sync_hdr {int /*<<< orphan*/  Command; int /*<<< orphan*/  StructureSize; } ;
struct smb2_sync_pdu {int /*<<< orphan*/  StructureSize2; struct smb2_sync_hdr sync_hdr; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int* has_smb2_data_area ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb2_get_data_area_len (int*,int*,struct smb2_sync_hdr*) ; 

unsigned int
smb2_calc_size(void *buf, struct TCP_Server_Info *srvr)
{
	struct smb2_sync_pdu *pdu = (struct smb2_sync_pdu *)buf;
	struct smb2_sync_hdr *shdr = &pdu->sync_hdr;
	int offset; /* the offset from the beginning of SMB to data area */
	int data_length; /* the length of the variable length data area */
	/* Structure Size has already been checked to make sure it is 64 */
	int len = le16_to_cpu(shdr->StructureSize);

	/*
	 * StructureSize2, ie length of fixed parameter area has already
	 * been checked to make sure it is the correct length.
	 */
	len += le16_to_cpu(pdu->StructureSize2);

	if (has_smb2_data_area[le16_to_cpu(shdr->Command)] == false)
		goto calc_size_exit;

	smb2_get_data_area_len(&offset, &data_length, shdr);
	cifs_dbg(FYI, "SMB2 data length %d offset %d\n", data_length, offset);

	if (data_length > 0) {
		/*
		 * Check to make sure that data area begins after fixed area,
		 * Note that last byte of the fixed area is part of data area
		 * for some commands, typically those with odd StructureSize,
		 * so we must add one to the calculation.
		 */
		if (offset + 1 < len) {
			cifs_dbg(VFS, "data area offset %d overlaps SMB2 header %d\n",
				 offset + 1, len);
			data_length = 0;
		} else {
			len = offset + data_length;
		}
	}
calc_size_exit:
	cifs_dbg(FYI, "SMB2 len %d\n", len);
	return len;
}