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
struct sa_defrag_extent_backref {scalar_t__ root_id; scalar_t__ inum; scalar_t__ file_pos; } ;

/* Variables and functions */

__attribute__((used)) static int backref_comp(struct sa_defrag_extent_backref *b1,
			struct sa_defrag_extent_backref *b2)
{
	if (b1->root_id < b2->root_id)
		return -1;
	else if (b1->root_id > b2->root_id)
		return 1;

	if (b1->inum < b2->inum)
		return -1;
	else if (b1->inum > b2->inum)
		return 1;

	if (b1->file_pos < b2->file_pos)
		return -1;
	else if (b1->file_pos > b2->file_pos)
		return 1;

	/*
	 * [------------------------------] ===> (a range of space)
	 *     |<--->|   |<---->| =============> (fs/file tree A)
	 * |<---------------------------->| ===> (fs/file tree B)
	 *
	 * A range of space can refer to two file extents in one tree while
	 * refer to only one file extent in another tree.
	 *
	 * So we may process a disk offset more than one time(two extents in A)
	 * and locate at the same extent(one extent in B), then insert two same
	 * backrefs(both refer to the extent in B).
	 */
	return 0;
}