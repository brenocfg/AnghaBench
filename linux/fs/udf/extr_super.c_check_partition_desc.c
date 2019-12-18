#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct udf_part_map {scalar_t__ s_partition_type; } ;
struct super_block {int dummy; } ;
struct TYPE_10__ {int extLength; } ;
struct TYPE_9__ {int extLength; } ;
struct TYPE_8__ {int extLength; } ;
struct TYPE_7__ {int extLength; } ;
struct partitionHeaderDesc {TYPE_5__ freedSpaceBitmap; TYPE_4__ freedSpaceTable; TYPE_3__ unallocSpaceBitmap; TYPE_2__ unallocSpaceTable; } ;
struct TYPE_6__ {int /*<<< orphan*/  ident; } ;
struct partitionDesc {scalar_t__ partitionContentsUse; TYPE_1__ partitionContents; int /*<<< orphan*/  accessType; } ;

/* Variables and functions */
 int EACCES ; 
#define  PD_ACCESS_TYPE_NONE 131 
#define  PD_ACCESS_TYPE_READ_ONLY 130 
#define  PD_ACCESS_TYPE_REWRITABLE 129 
#define  PD_ACCESS_TYPE_WRITE_ONCE 128 
 int /*<<< orphan*/  PD_PARTITION_CONTENTS_NSR02 ; 
 int /*<<< orphan*/  PD_PARTITION_CONTENTS_NSR03 ; 
 int /*<<< orphan*/  UDF_FLAG_RW_INCOMPAT ; 
 int /*<<< orphan*/  UDF_SET_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ UDF_VIRTUAL_MAP15 ; 
 scalar_t__ UDF_VIRTUAL_MAP20 ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_partition_desc(struct super_block *sb,
				struct partitionDesc *p,
				struct udf_part_map *map)
{
	bool umap, utable, fmap, ftable;
	struct partitionHeaderDesc *phd;

	switch (le32_to_cpu(p->accessType)) {
	case PD_ACCESS_TYPE_READ_ONLY:
	case PD_ACCESS_TYPE_WRITE_ONCE:
	case PD_ACCESS_TYPE_REWRITABLE:
	case PD_ACCESS_TYPE_NONE:
		goto force_ro;
	}

	/* No Partition Header Descriptor? */
	if (strcmp(p->partitionContents.ident, PD_PARTITION_CONTENTS_NSR02) &&
	    strcmp(p->partitionContents.ident, PD_PARTITION_CONTENTS_NSR03))
		goto force_ro;

	phd = (struct partitionHeaderDesc *)p->partitionContentsUse;
	utable = phd->unallocSpaceTable.extLength;
	umap = phd->unallocSpaceBitmap.extLength;
	ftable = phd->freedSpaceTable.extLength;
	fmap = phd->freedSpaceBitmap.extLength;

	/* No allocation info? */
	if (!utable && !umap && !ftable && !fmap)
		goto force_ro;

	/* We don't support blocks that require erasing before overwrite */
	if (ftable || fmap)
		goto force_ro;
	/* UDF 2.60: 2.3.3 - no mixing of tables & bitmaps, no VAT. */
	if (utable && umap)
		goto force_ro;

	if (map->s_partition_type == UDF_VIRTUAL_MAP15 ||
	    map->s_partition_type == UDF_VIRTUAL_MAP20)
		goto force_ro;

	return 0;
force_ro:
	if (!sb_rdonly(sb))
		return -EACCES;
	UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
	return 0;
}