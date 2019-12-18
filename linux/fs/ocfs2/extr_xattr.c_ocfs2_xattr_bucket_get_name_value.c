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
typedef  int u16 ;
struct super_block {int s_blocksize_bits; int s_blocksize; } ;
struct ocfs2_xattr_header {TYPE_1__* xh_entries; int /*<<< orphan*/  xh_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  xe_name_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xattr_bucket_get_name_value(struct super_block *sb,
					     struct ocfs2_xattr_header *xh,
					     int index,
					     int *block_off,
					     int *new_offset)
{
	u16 name_offset;

	if (index < 0 || index >= le16_to_cpu(xh->xh_count))
		return -EINVAL;

	name_offset = le16_to_cpu(xh->xh_entries[index].xe_name_offset);

	*block_off = name_offset >> sb->s_blocksize_bits;
	*new_offset = name_offset % sb->s_blocksize;

	return 0;
}