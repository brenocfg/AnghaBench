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
struct virtual_item {struct direntry_uarea* vi_uarea; } ;
struct direntry_uarea {int entry_count; int* entry_sizes; int flags; } ;

/* Variables and functions */
 int DIRENTRY_VI_FIRST_DIRENTRY_ITEM ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ *,char*,char*,int,int) ; 

__attribute__((used)) static int direntry_check_left(struct virtual_item *vi, int free,
			       int start_skip, int end_skip)
{
	int i;
	int entries = 0;
	struct direntry_uarea *dir_u = vi->vi_uarea;

	for (i = start_skip; i < dir_u->entry_count - end_skip; i++) {
		/* i-th entry doesn't fit into the remaining free space */
		if (dir_u->entry_sizes[i] > free)
			break;

		free -= dir_u->entry_sizes[i];
		entries++;
	}

	if (entries == dir_u->entry_count) {
		reiserfs_panic(NULL, "item_ops-1",
			       "free space %d, entry_count %d", free,
			       dir_u->entry_count);
	}

	/* "." and ".." can not be separated from each other */
	if (start_skip == 0 && (dir_u->flags & DIRENTRY_VI_FIRST_DIRENTRY_ITEM)
	    && entries < 2)
		entries = 0;

	return entries ? : -1;
}