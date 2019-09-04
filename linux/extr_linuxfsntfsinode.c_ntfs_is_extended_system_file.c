#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_17__ {TYPE_5__* ntfs_ino; TYPE_1__* mrec; TYPE_8__* attr; } ;
typedef  TYPE_6__ ntfs_attr_search_ctx ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  value_length; int /*<<< orphan*/  value_offset; } ;
struct TYPE_14__ {TYPE_2__ resident; } ;
struct TYPE_19__ {TYPE_3__ data; scalar_t__ flags; scalar_t__ non_resident; int /*<<< orphan*/  length; } ;
struct TYPE_18__ {int /*<<< orphan*/  parent_directory; } ;
struct TYPE_16__ {TYPE_4__* vol; } ;
struct TYPE_15__ {int /*<<< orphan*/  sb; } ;
struct TYPE_12__ {int /*<<< orphan*/  bytes_in_use; int /*<<< orphan*/  link_count; } ;
typedef  TYPE_7__ FILE_NAME_ATTR ;
typedef  TYPE_8__ ATTR_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FILE_NAME ; 
 int EIO ; 
 int ENOENT ; 
 scalar_t__ FILE_Extend ; 
 scalar_t__ MREF_LE (int /*<<< orphan*/ ) ; 
 int RESIDENT_ATTR_IS_INDEXED ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ntfs_attr_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ntfs_attr_reinit_search_ctx (TYPE_6__*) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ntfs_is_extended_system_file(ntfs_attr_search_ctx *ctx)
{
	int nr_links, err;

	/* Restart search. */
	ntfs_attr_reinit_search_ctx(ctx);

	/* Get number of hard links. */
	nr_links = le16_to_cpu(ctx->mrec->link_count);

	/* Loop through all hard links. */
	while (!(err = ntfs_attr_lookup(AT_FILE_NAME, NULL, 0, 0, 0, NULL, 0,
			ctx))) {
		FILE_NAME_ATTR *file_name_attr;
		ATTR_RECORD *attr = ctx->attr;
		u8 *p, *p2;

		nr_links--;
		/*
		 * Maximum sanity checking as we are called on an inode that
		 * we suspect might be corrupt.
		 */
		p = (u8*)attr + le32_to_cpu(attr->length);
		if (p < (u8*)ctx->mrec || (u8*)p > (u8*)ctx->mrec +
				le32_to_cpu(ctx->mrec->bytes_in_use)) {
err_corrupt_attr:
			ntfs_error(ctx->ntfs_ino->vol->sb, "Corrupt file name "
					"attribute. You should run chkdsk.");
			return -EIO;
		}
		if (attr->non_resident) {
			ntfs_error(ctx->ntfs_ino->vol->sb, "Non-resident file "
					"name. You should run chkdsk.");
			return -EIO;
		}
		if (attr->flags) {
			ntfs_error(ctx->ntfs_ino->vol->sb, "File name with "
					"invalid flags. You should run "
					"chkdsk.");
			return -EIO;
		}
		if (!(attr->data.resident.flags & RESIDENT_ATTR_IS_INDEXED)) {
			ntfs_error(ctx->ntfs_ino->vol->sb, "Unindexed file "
					"name. You should run chkdsk.");
			return -EIO;
		}
		file_name_attr = (FILE_NAME_ATTR*)((u8*)attr +
				le16_to_cpu(attr->data.resident.value_offset));
		p2 = (u8*)attr + le32_to_cpu(attr->data.resident.value_length);
		if (p2 < (u8*)attr || p2 > p)
			goto err_corrupt_attr;
		/* This attribute is ok, but is it in the $Extend directory? */
		if (MREF_LE(file_name_attr->parent_directory) == FILE_Extend)
			return 1;	/* YES, it's an extended system file. */
	}
	if (unlikely(err != -ENOENT))
		return err;
	if (unlikely(nr_links)) {
		ntfs_error(ctx->ntfs_ino->vol->sb, "Inode hard link count "
				"doesn't match number of name attributes. You "
				"should run chkdsk.");
		return -EIO;
	}
	return 0;	/* NO, it is not an extended system file. */
}