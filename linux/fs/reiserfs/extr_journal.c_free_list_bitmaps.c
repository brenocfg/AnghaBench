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
struct super_block {int dummy; } ;
struct reiserfs_list_bitmap {int /*<<< orphan*/ * bitmaps; int /*<<< orphan*/ * journal_list; } ;

/* Variables and functions */
 int JOURNAL_NUM_BITMAPS ; 
 int /*<<< orphan*/  cleanup_bitmap_list (struct super_block*,struct reiserfs_list_bitmap*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int free_list_bitmaps(struct super_block *sb,
			     struct reiserfs_list_bitmap *jb_array)
{
	int i;
	struct reiserfs_list_bitmap *jb;
	for (i = 0; i < JOURNAL_NUM_BITMAPS; i++) {
		jb = jb_array + i;
		jb->journal_list = NULL;
		cleanup_bitmap_list(sb, jb);
		vfree(jb->bitmaps);
		jb->bitmaps = NULL;
	}
	return 0;
}