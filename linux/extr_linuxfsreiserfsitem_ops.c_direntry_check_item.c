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
struct reiserfs_de_head {int dummy; } ;
struct item_head {int dummy; } ;

/* Variables and functions */
 int ih_entry_count (struct item_head*) ; 

__attribute__((used)) static void direntry_check_item(struct item_head *ih, char *item)
{
	int i;
	struct reiserfs_de_head *deh;

	/* unused */
	deh = (struct reiserfs_de_head *)item;
	for (i = 0; i < ih_entry_count(ih); i++, deh++) {
		;
	}
}