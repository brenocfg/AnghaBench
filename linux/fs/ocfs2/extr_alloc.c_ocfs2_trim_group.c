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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct super_block {int dummy; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_free_bits_count; int /*<<< orphan*/  bg_blkno; void* bg_bitmap; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_find_next_bit (void*,int,int) ; 
 int ocfs2_find_next_zero_bit (void*,int,int) ; 
 int ocfs2_trim_extent (struct super_block*,struct ocfs2_group_desc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  trace_ocfs2_trim_group (unsigned long long,int,int,int) ; 

__attribute__((used)) static int ocfs2_trim_group(struct super_block *sb,
			    struct ocfs2_group_desc *gd, u64 group,
			    u32 start, u32 max, u32 minbits)
{
	int ret = 0, count = 0, next;
	void *bitmap = gd->bg_bitmap;

	if (le16_to_cpu(gd->bg_free_bits_count) < minbits)
		return 0;

	trace_ocfs2_trim_group((unsigned long long)le64_to_cpu(gd->bg_blkno),
			       start, max, minbits);

	while (start < max) {
		start = ocfs2_find_next_zero_bit(bitmap, max, start);
		if (start >= max)
			break;
		next = ocfs2_find_next_bit(bitmap, max, start);

		if ((next - start) >= minbits) {
			ret = ocfs2_trim_extent(sb, gd, group,
						start, next - start);
			if (ret < 0) {
				mlog_errno(ret);
				break;
			}
			count += next - start;
		}
		start = next + 1;

		if (fatal_signal_pending(current)) {
			count = -ERESTARTSYS;
			break;
		}

		if ((le16_to_cpu(gd->bg_free_bits_count) - count) < minbits)
			break;
	}

	if (ret < 0)
		count = ret;

	return count;
}