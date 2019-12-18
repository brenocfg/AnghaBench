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
struct reiserfs_list_bitmap {int /*<<< orphan*/ ** bitmaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_bitmap_node (struct super_block*,int /*<<< orphan*/ *) ; 
 int reiserfs_bmap_count (struct super_block*) ; 

__attribute__((used)) static void cleanup_bitmap_list(struct super_block *sb,
				struct reiserfs_list_bitmap *jb)
{
	int i;
	if (jb->bitmaps == NULL)
		return;

	for (i = 0; i < reiserfs_bmap_count(sb); i++) {
		if (jb->bitmaps[i]) {
			free_bitmap_node(sb, jb->bitmaps[i]);
			jb->bitmaps[i] = NULL;
		}
	}
}