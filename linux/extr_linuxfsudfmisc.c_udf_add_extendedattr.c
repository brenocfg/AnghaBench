#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct udf_sb_info {int s_udfrev; int s_serial_number; } ;
struct TYPE_6__ {int logicalBlockNum; } ;
struct TYPE_5__ {int* i_data; } ;
struct udf_inode_info {int i_lenEAttr; int i_lenAlloc; TYPE_2__ i_location; TYPE_1__ i_ext; } ;
struct tag {int dummy; } ;
struct inode {TYPE_4__* i_sb; } ;
struct genericFormat {int dummy; } ;
struct TYPE_7__ {void* tagIdent; int /*<<< orphan*/  tagChecksum; void* descCRC; void* descCRCLength; void* tagLocation; void* tagSerialNum; void* descVersion; } ;
struct extendedAttrHeaderDesc {TYPE_3__ descTag; void* appAttrLocation; void* impAttrLocation; } ;
struct TYPE_8__ {int s_blocksize; } ;

/* Variables and functions */
 int TAG_IDENT_EAHD ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 struct udf_sb_info* UDF_SB (TYPE_4__*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int crc_itu_t (int /*<<< orphan*/ ,char*,int) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int udf_file_entry_alloc_offset (struct inode*) ; 
 int /*<<< orphan*/  udf_tag_checksum (TYPE_3__*) ; 

struct genericFormat *udf_add_extendedattr(struct inode *inode, uint32_t size,
					   uint32_t type, uint8_t loc)
{
	uint8_t *ea = NULL, *ad = NULL;
	int offset;
	uint16_t crclen;
	struct udf_inode_info *iinfo = UDF_I(inode);

	ea = iinfo->i_ext.i_data;
	if (iinfo->i_lenEAttr) {
		ad = iinfo->i_ext.i_data + iinfo->i_lenEAttr;
	} else {
		ad = ea;
		size += sizeof(struct extendedAttrHeaderDesc);
	}

	offset = inode->i_sb->s_blocksize - udf_file_entry_alloc_offset(inode) -
		iinfo->i_lenAlloc;

	/* TODO - Check for FreeEASpace */

	if (loc & 0x01 && offset >= size) {
		struct extendedAttrHeaderDesc *eahd;
		eahd = (struct extendedAttrHeaderDesc *)ea;

		if (iinfo->i_lenAlloc)
			memmove(&ad[size], ad, iinfo->i_lenAlloc);

		if (iinfo->i_lenEAttr) {
			/* check checksum/crc */
			if (eahd->descTag.tagIdent !=
					cpu_to_le16(TAG_IDENT_EAHD) ||
			    le32_to_cpu(eahd->descTag.tagLocation) !=
					iinfo->i_location.logicalBlockNum)
				return NULL;
		} else {
			struct udf_sb_info *sbi = UDF_SB(inode->i_sb);

			size -= sizeof(struct extendedAttrHeaderDesc);
			iinfo->i_lenEAttr +=
				sizeof(struct extendedAttrHeaderDesc);
			eahd->descTag.tagIdent = cpu_to_le16(TAG_IDENT_EAHD);
			if (sbi->s_udfrev >= 0x0200)
				eahd->descTag.descVersion = cpu_to_le16(3);
			else
				eahd->descTag.descVersion = cpu_to_le16(2);
			eahd->descTag.tagSerialNum =
					cpu_to_le16(sbi->s_serial_number);
			eahd->descTag.tagLocation = cpu_to_le32(
					iinfo->i_location.logicalBlockNum);
			eahd->impAttrLocation = cpu_to_le32(0xFFFFFFFF);
			eahd->appAttrLocation = cpu_to_le32(0xFFFFFFFF);
		}

		offset = iinfo->i_lenEAttr;
		if (type < 2048) {
			if (le32_to_cpu(eahd->appAttrLocation) <
					iinfo->i_lenEAttr) {
				uint32_t aal =
					le32_to_cpu(eahd->appAttrLocation);
				memmove(&ea[offset - aal + size],
					&ea[aal], offset - aal);
				offset -= aal;
				eahd->appAttrLocation =
						cpu_to_le32(aal + size);
			}
			if (le32_to_cpu(eahd->impAttrLocation) <
					iinfo->i_lenEAttr) {
				uint32_t ial =
					le32_to_cpu(eahd->impAttrLocation);
				memmove(&ea[offset - ial + size],
					&ea[ial], offset - ial);
				offset -= ial;
				eahd->impAttrLocation =
						cpu_to_le32(ial + size);
			}
		} else if (type < 65536) {
			if (le32_to_cpu(eahd->appAttrLocation) <
					iinfo->i_lenEAttr) {
				uint32_t aal =
					le32_to_cpu(eahd->appAttrLocation);
				memmove(&ea[offset - aal + size],
					&ea[aal], offset - aal);
				offset -= aal;
				eahd->appAttrLocation =
						cpu_to_le32(aal + size);
			}
		}
		/* rewrite CRC + checksum of eahd */
		crclen = sizeof(struct extendedAttrHeaderDesc) - sizeof(struct tag);
		eahd->descTag.descCRCLength = cpu_to_le16(crclen);
		eahd->descTag.descCRC = cpu_to_le16(crc_itu_t(0, (char *)eahd +
						sizeof(struct tag), crclen));
		eahd->descTag.tagChecksum = udf_tag_checksum(&eahd->descTag);
		iinfo->i_lenEAttr += size;
		return (struct genericFormat *)&ea[offset];
	}

	return NULL;
}