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
struct reiserfs_list_bitmap {int /*<<< orphan*/ * journal_list; } ;
struct reiserfs_journal_list {struct reiserfs_list_bitmap* j_list_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_bitmap_list (struct super_block*,struct reiserfs_list_bitmap*) ; 

__attribute__((used)) static void cleanup_freed_for_journal_list(struct super_block *sb,
					   struct reiserfs_journal_list *jl)
{

	struct reiserfs_list_bitmap *jb = jl->j_list_bitmap;
	if (jb) {
		cleanup_bitmap_list(sb, jb);
	}
	jl->j_list_bitmap->journal_list = NULL;
	jl->j_list_bitmap = NULL;
}