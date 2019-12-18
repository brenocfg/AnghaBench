#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_xattr_tree_list {int /*<<< orphan*/  result; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer; } ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_len; } ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {struct ocfs2_xattr_entry* xh_entries; int /*<<< orphan*/  xh_count; } ;

/* Variables and functions */
 scalar_t__ bucket_block (struct ocfs2_xattr_bucket*,int) ; 
 TYPE_1__* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_bucket_get_name_value (int /*<<< orphan*/ ,TYPE_1__*,int,int*,int*) ; 
 int ocfs2_xattr_get_type (struct ocfs2_xattr_entry*) ; 
 int ocfs2_xattr_list_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_list_xattr_bucket(struct inode *inode,
				   struct ocfs2_xattr_bucket *bucket,
				   void *para)
{
	int ret = 0, type;
	struct ocfs2_xattr_tree_list *xl = (struct ocfs2_xattr_tree_list *)para;
	int i, block_off, new_offset;
	const char *name;

	for (i = 0 ; i < le16_to_cpu(bucket_xh(bucket)->xh_count); i++) {
		struct ocfs2_xattr_entry *entry = &bucket_xh(bucket)->xh_entries[i];
		type = ocfs2_xattr_get_type(entry);

		ret = ocfs2_xattr_bucket_get_name_value(inode->i_sb,
							bucket_xh(bucket),
							i,
							&block_off,
							&new_offset);
		if (ret)
			break;

		name = (const char *)bucket_block(bucket, block_off) +
			new_offset;
		ret = ocfs2_xattr_list_entry(inode->i_sb,
					     xl->buffer,
					     xl->buffer_size,
					     &xl->result,
					     type, name,
					     entry->xe_name_len);
		if (ret)
			break;
	}

	return ret;
}