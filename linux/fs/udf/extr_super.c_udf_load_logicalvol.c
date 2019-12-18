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
typedef  scalar_t__ uint16_t ;
typedef  int u16 ;
struct udf_sb_info {int s_partitions; int /*<<< orphan*/  s_lvid_bh; struct udf_part_map* s_partmaps; } ;
struct udf_meta_data {int /*<<< orphan*/  s_flags; void* s_align_unit_size; void* s_alloc_unit_size; void* s_bitmap_file_loc; void* s_mirror_file_loc; void* s_meta_file_loc; } ;
struct TYPE_5__ {struct udf_meta_data s_metadata; } ;
struct udf_part_map {void* s_volumeseqnum; void* s_partition_num; int /*<<< orphan*/ * s_partition_func; int /*<<< orphan*/  s_partition_type; TYPE_1__ s_type_specific; } ;
struct TYPE_7__ {int /*<<< orphan*/  ident; scalar_t__ identSuffix; } ;
struct udfPartitionMap2 {int /*<<< orphan*/  partitionNum; int /*<<< orphan*/  volSeqNum; TYPE_3__ partIdent; } ;
struct super_block {int s_blocksize; } ;
struct sparablePartitionMap {int dummy; } ;
struct TYPE_6__ {scalar_t__ identSuffix; } ;
struct metadataPartitionMap {int flags; int /*<<< orphan*/  metadataBitmapFileLoc; int /*<<< orphan*/  metadataMirrorFileLoc; int /*<<< orphan*/  metadataFileLoc; int /*<<< orphan*/  allocUnitSize; int /*<<< orphan*/  partitionNum; TYPE_2__ partIdent; int /*<<< orphan*/  alignUnitSize; } ;
struct long_ad {int /*<<< orphan*/  extLocation; } ;
struct TYPE_8__ {scalar_t__ extLength; } ;
struct logicalVolDesc {TYPE_4__ integritySeqExt; int /*<<< orphan*/ * logicalVolContentsUse; int /*<<< orphan*/ * partitionMaps; int /*<<< orphan*/  numPartitionMaps; int /*<<< orphan*/  domainIdent; int /*<<< orphan*/  mapTableLength; } ;
struct kernel_lb_addr {int partitionReferenceNum; int /*<<< orphan*/  logicalBlockNum; } ;
struct genericPartitionMap1 {int /*<<< orphan*/  partitionNum; int /*<<< orphan*/  volSeqNum; } ;
struct genericPartitionMap {int partitionMapType; scalar_t__ partitionMapLength; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EACCES ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  MF_DUPLICATE_MD ; 
 scalar_t__ TAG_IDENT_LVD ; 
 int /*<<< orphan*/  UDF_FLAG_RW_INCOMPAT ; 
 int /*<<< orphan*/  UDF_ID_METADATA ; 
 int /*<<< orphan*/  UDF_ID_SPARABLE ; 
 int /*<<< orphan*/  UDF_ID_VIRTUAL ; 
 int /*<<< orphan*/  UDF_METADATA_MAP25 ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  UDF_SET_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDF_TYPE1_MAP15 ; 
 int /*<<< orphan*/  UDF_VIRTUAL_MAP15 ; 
 int /*<<< orphan*/  UDF_VIRTUAL_MAP20 ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leea_to_cpu (TYPE_4__) ; 
 struct kernel_lb_addr lelb_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*,int,...) ; 
 int /*<<< orphan*/  udf_err (struct super_block*,char*,unsigned int,int) ; 
 int /*<<< orphan*/ * udf_get_pblock_meta25 ; 
 int /*<<< orphan*/ * udf_get_pblock_virt15 ; 
 int /*<<< orphan*/ * udf_get_pblock_virt20 ; 
 int /*<<< orphan*/  udf_load_logicalvolint (struct super_block*,int /*<<< orphan*/ ) ; 
 int udf_load_sparable_map (struct super_block*,struct udf_part_map*,struct sparablePartitionMap*) ; 
 struct buffer_head* udf_read_tagged (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int udf_sb_alloc_partition_maps (struct super_block*,void*) ; 
 int udf_verify_domain_identifier (struct super_block*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  udf_warn (struct super_block*,char*) ; 

__attribute__((used)) static int udf_load_logicalvol(struct super_block *sb, sector_t block,
			       struct kernel_lb_addr *fileset)
{
	struct logicalVolDesc *lvd;
	int i, offset;
	uint8_t type;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct genericPartitionMap *gpm;
	uint16_t ident;
	struct buffer_head *bh;
	unsigned int table_len;
	int ret;

	bh = udf_read_tagged(sb, block, block, &ident);
	if (!bh)
		return -EAGAIN;
	BUG_ON(ident != TAG_IDENT_LVD);
	lvd = (struct logicalVolDesc *)bh->b_data;
	table_len = le32_to_cpu(lvd->mapTableLength);
	if (table_len > sb->s_blocksize - sizeof(*lvd)) {
		udf_err(sb, "error loading logical volume descriptor: "
			"Partition table too long (%u > %lu)\n", table_len,
			sb->s_blocksize - sizeof(*lvd));
		ret = -EIO;
		goto out_bh;
	}

	ret = udf_verify_domain_identifier(sb, &lvd->domainIdent,
					   "logical volume");
	if (ret)
		goto out_bh;
	ret = udf_sb_alloc_partition_maps(sb, le32_to_cpu(lvd->numPartitionMaps));
	if (ret)
		goto out_bh;

	for (i = 0, offset = 0;
	     i < sbi->s_partitions && offset < table_len;
	     i++, offset += gpm->partitionMapLength) {
		struct udf_part_map *map = &sbi->s_partmaps[i];
		gpm = (struct genericPartitionMap *)
				&(lvd->partitionMaps[offset]);
		type = gpm->partitionMapType;
		if (type == 1) {
			struct genericPartitionMap1 *gpm1 =
				(struct genericPartitionMap1 *)gpm;
			map->s_partition_type = UDF_TYPE1_MAP15;
			map->s_volumeseqnum = le16_to_cpu(gpm1->volSeqNum);
			map->s_partition_num = le16_to_cpu(gpm1->partitionNum);
			map->s_partition_func = NULL;
		} else if (type == 2) {
			struct udfPartitionMap2 *upm2 =
						(struct udfPartitionMap2 *)gpm;
			if (!strncmp(upm2->partIdent.ident, UDF_ID_VIRTUAL,
						strlen(UDF_ID_VIRTUAL))) {
				u16 suf =
					le16_to_cpu(((__le16 *)upm2->partIdent.
							identSuffix)[0]);
				if (suf < 0x0200) {
					map->s_partition_type =
							UDF_VIRTUAL_MAP15;
					map->s_partition_func =
							udf_get_pblock_virt15;
				} else {
					map->s_partition_type =
							UDF_VIRTUAL_MAP20;
					map->s_partition_func =
							udf_get_pblock_virt20;
				}
			} else if (!strncmp(upm2->partIdent.ident,
						UDF_ID_SPARABLE,
						strlen(UDF_ID_SPARABLE))) {
				ret = udf_load_sparable_map(sb, map,
					(struct sparablePartitionMap *)gpm);
				if (ret < 0)
					goto out_bh;
			} else if (!strncmp(upm2->partIdent.ident,
						UDF_ID_METADATA,
						strlen(UDF_ID_METADATA))) {
				struct udf_meta_data *mdata =
					&map->s_type_specific.s_metadata;
				struct metadataPartitionMap *mdm =
						(struct metadataPartitionMap *)
						&(lvd->partitionMaps[offset]);
				udf_debug("Parsing Logical vol part %d type %u  id=%s\n",
					  i, type, UDF_ID_METADATA);

				map->s_partition_type = UDF_METADATA_MAP25;
				map->s_partition_func = udf_get_pblock_meta25;

				mdata->s_meta_file_loc   =
					le32_to_cpu(mdm->metadataFileLoc);
				mdata->s_mirror_file_loc =
					le32_to_cpu(mdm->metadataMirrorFileLoc);
				mdata->s_bitmap_file_loc =
					le32_to_cpu(mdm->metadataBitmapFileLoc);
				mdata->s_alloc_unit_size =
					le32_to_cpu(mdm->allocUnitSize);
				mdata->s_align_unit_size =
					le16_to_cpu(mdm->alignUnitSize);
				if (mdm->flags & 0x01)
					mdata->s_flags |= MF_DUPLICATE_MD;

				udf_debug("Metadata Ident suffix=0x%x\n",
					  le16_to_cpu(*(__le16 *)
						      mdm->partIdent.identSuffix));
				udf_debug("Metadata part num=%u\n",
					  le16_to_cpu(mdm->partitionNum));
				udf_debug("Metadata part alloc unit size=%u\n",
					  le32_to_cpu(mdm->allocUnitSize));
				udf_debug("Metadata file loc=%u\n",
					  le32_to_cpu(mdm->metadataFileLoc));
				udf_debug("Mirror file loc=%u\n",
					  le32_to_cpu(mdm->metadataMirrorFileLoc));
				udf_debug("Bitmap file loc=%u\n",
					  le32_to_cpu(mdm->metadataBitmapFileLoc));
				udf_debug("Flags: %d %u\n",
					  mdata->s_flags, mdm->flags);
			} else {
				udf_debug("Unknown ident: %s\n",
					  upm2->partIdent.ident);
				continue;
			}
			map->s_volumeseqnum = le16_to_cpu(upm2->volSeqNum);
			map->s_partition_num = le16_to_cpu(upm2->partitionNum);
		}
		udf_debug("Partition (%d:%u) type %u on volume %u\n",
			  i, map->s_partition_num, type, map->s_volumeseqnum);
	}

	if (fileset) {
		struct long_ad *la = (struct long_ad *)&(lvd->logicalVolContentsUse[0]);

		*fileset = lelb_to_cpu(la->extLocation);
		udf_debug("FileSet found in LogicalVolDesc at block=%u, partition=%u\n",
			  fileset->logicalBlockNum,
			  fileset->partitionReferenceNum);
	}
	if (lvd->integritySeqExt.extLength)
		udf_load_logicalvolint(sb, leea_to_cpu(lvd->integritySeqExt));
	ret = 0;

	if (!sbi->s_lvid_bh) {
		/* We can't generate unique IDs without a valid LVID */
		if (sb_rdonly(sb)) {
			UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
		} else {
			udf_warn(sb, "Damaged or missing LVID, forcing "
				     "readonly mount\n");
			ret = -EACCES;
		}
	}
out_bh:
	brelse(bh);
	return ret;
}