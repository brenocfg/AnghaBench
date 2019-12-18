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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ u8 ;
struct tag {scalar_t__ tagIdent; scalar_t__ tagChecksum; scalar_t__ descVersion; scalar_t__ descCRCLength; scalar_t__ descCRC; int /*<<< orphan*/  tagLocation; } ;
struct super_block {int s_blocksize; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int crc_itu_t (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int le16_to_cpu (scalar_t__) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  udf_err (struct super_block*,char*,int,int,...) ; 
 scalar_t__ udf_tag_checksum (struct tag*) ; 
 struct buffer_head* udf_tread (struct super_block*,int) ; 

struct buffer_head *udf_read_tagged(struct super_block *sb, uint32_t block,
				    uint32_t location, uint16_t *ident)
{
	struct tag *tag_p;
	struct buffer_head *bh = NULL;
	u8 checksum;

	/* Read the block */
	if (block == 0xFFFFFFFF)
		return NULL;

	bh = udf_tread(sb, block);
	if (!bh) {
		udf_err(sb, "read failed, block=%u, location=%u\n",
			block, location);
		return NULL;
	}

	tag_p = (struct tag *)(bh->b_data);

	*ident = le16_to_cpu(tag_p->tagIdent);

	if (location != le32_to_cpu(tag_p->tagLocation)) {
		udf_debug("location mismatch block %u, tag %u != %u\n",
			  block, le32_to_cpu(tag_p->tagLocation), location);
		goto error_out;
	}

	/* Verify the tag checksum */
	checksum = udf_tag_checksum(tag_p);
	if (checksum != tag_p->tagChecksum) {
		udf_err(sb, "tag checksum failed, block %u: 0x%02x != 0x%02x\n",
			block, checksum, tag_p->tagChecksum);
		goto error_out;
	}

	/* Verify the tag version */
	if (tag_p->descVersion != cpu_to_le16(0x0002U) &&
	    tag_p->descVersion != cpu_to_le16(0x0003U)) {
		udf_err(sb, "tag version 0x%04x != 0x0002 || 0x0003, block %u\n",
			le16_to_cpu(tag_p->descVersion), block);
		goto error_out;
	}

	/* Verify the descriptor CRC */
	if (le16_to_cpu(tag_p->descCRCLength) + sizeof(struct tag) > sb->s_blocksize ||
	    le16_to_cpu(tag_p->descCRC) == crc_itu_t(0,
					bh->b_data + sizeof(struct tag),
					le16_to_cpu(tag_p->descCRCLength)))
		return bh;

	udf_debug("Crc failure block %u: crc = %u, crclen = %u\n", block,
		  le16_to_cpu(tag_p->descCRC),
		  le16_to_cpu(tag_p->descCRCLength));
error_out:
	brelse(bh);
	return NULL;
}