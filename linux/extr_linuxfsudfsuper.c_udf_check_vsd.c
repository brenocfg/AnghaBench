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
struct volStructDesc {int structType; int /*<<< orphan*/  stdIdent; } ;
struct udf_sb_info {int s_session; } ;
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int loff_t ;

/* Variables and functions */
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int VSD_FIRST_SECTOR_OFFSET ; 
 int VSD_MAX_SECTOR_OFFSET ; 
 int /*<<< orphan*/  VSD_STD_ID_BEA01 ; 
 int /*<<< orphan*/  VSD_STD_ID_BOOT2 ; 
 int /*<<< orphan*/  VSD_STD_ID_CD001 ; 
 int /*<<< orphan*/  VSD_STD_ID_CDW02 ; 
 int /*<<< orphan*/  VSD_STD_ID_LEN ; 
 int /*<<< orphan*/  VSD_STD_ID_NSR02 ; 
 int /*<<< orphan*/  VSD_STD_ID_NSR03 ; 
 int /*<<< orphan*/  VSD_STD_ID_TEA01 ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*,...) ; 
 struct buffer_head* udf_tread (struct super_block*,int) ; 

__attribute__((used)) static loff_t udf_check_vsd(struct super_block *sb)
{
	struct volStructDesc *vsd = NULL;
	loff_t sector = VSD_FIRST_SECTOR_OFFSET;
	int sectorsize;
	struct buffer_head *bh = NULL;
	int nsr02 = 0;
	int nsr03 = 0;
	struct udf_sb_info *sbi;

	sbi = UDF_SB(sb);
	if (sb->s_blocksize < sizeof(struct volStructDesc))
		sectorsize = sizeof(struct volStructDesc);
	else
		sectorsize = sb->s_blocksize;

	sector += (((loff_t)sbi->s_session) << sb->s_blocksize_bits);

	udf_debug("Starting at sector %u (%lu byte sectors)\n",
		  (unsigned int)(sector >> sb->s_blocksize_bits),
		  sb->s_blocksize);
	/* Process the sequence (if applicable). The hard limit on the sector
	 * offset is arbitrary, hopefully large enough so that all valid UDF
	 * filesystems will be recognised. There is no mention of an upper
	 * bound to the size of the volume recognition area in the standard.
	 *  The limit will prevent the code to read all the sectors of a
	 * specially crafted image (like a bluray disc full of CD001 sectors),
	 * potentially causing minutes or even hours of uninterruptible I/O
	 * activity. This actually happened with uninitialised SSD partitions
	 * (all 0xFF) before the check for the limit and all valid IDs were
	 * added */
	for (; !nsr02 && !nsr03 && sector < VSD_MAX_SECTOR_OFFSET;
	     sector += sectorsize) {
		/* Read a block */
		bh = udf_tread(sb, sector >> sb->s_blocksize_bits);
		if (!bh)
			break;

		/* Look for ISO  descriptors */
		vsd = (struct volStructDesc *)(bh->b_data +
					      (sector & (sb->s_blocksize - 1)));

		if (!strncmp(vsd->stdIdent, VSD_STD_ID_CD001,
				    VSD_STD_ID_LEN)) {
			switch (vsd->structType) {
			case 0:
				udf_debug("ISO9660 Boot Record found\n");
				break;
			case 1:
				udf_debug("ISO9660 Primary Volume Descriptor found\n");
				break;
			case 2:
				udf_debug("ISO9660 Supplementary Volume Descriptor found\n");
				break;
			case 3:
				udf_debug("ISO9660 Volume Partition Descriptor found\n");
				break;
			case 255:
				udf_debug("ISO9660 Volume Descriptor Set Terminator found\n");
				break;
			default:
				udf_debug("ISO9660 VRS (%u) found\n",
					  vsd->structType);
				break;
			}
		} else if (!strncmp(vsd->stdIdent, VSD_STD_ID_BEA01,
				    VSD_STD_ID_LEN))
			; /* nothing */
		else if (!strncmp(vsd->stdIdent, VSD_STD_ID_TEA01,
				    VSD_STD_ID_LEN)) {
			brelse(bh);
			break;
		} else if (!strncmp(vsd->stdIdent, VSD_STD_ID_NSR02,
				    VSD_STD_ID_LEN))
			nsr02 = sector;
		else if (!strncmp(vsd->stdIdent, VSD_STD_ID_NSR03,
				    VSD_STD_ID_LEN))
			nsr03 = sector;
		else if (!strncmp(vsd->stdIdent, VSD_STD_ID_BOOT2,
				    VSD_STD_ID_LEN))
			; /* nothing */
		else if (!strncmp(vsd->stdIdent, VSD_STD_ID_CDW02,
				    VSD_STD_ID_LEN))
			; /* nothing */
		else {
			/* invalid id : end of volume recognition area */
			brelse(bh);
			break;
		}
		brelse(bh);
	}

	if (nsr03)
		return nsr03;
	else if (nsr02)
		return nsr02;
	else if (!bh && sector - (sbi->s_session << sb->s_blocksize_bits) ==
			VSD_FIRST_SECTOR_OFFSET)
		return -1;
	else
		return 0;
}