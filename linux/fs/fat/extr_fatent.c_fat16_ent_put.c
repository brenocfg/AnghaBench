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
struct TYPE_2__ {int /*<<< orphan*/ * ent16_p; } ;
struct fat_entry {int /*<<< orphan*/  fat_inode; int /*<<< orphan*/ * bhs; TYPE_1__ u; } ;

/* Variables and functions */
 int EOF_FAT16 ; 
 int FAT_ENT_EOF ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fat16_ent_put(struct fat_entry *fatent, int new)
{
	if (new == FAT_ENT_EOF)
		new = EOF_FAT16;

	*fatent->u.ent16_p = cpu_to_le16(new);
	mark_buffer_dirty_inode(fatent->bhs[0], fatent->fat_inode);
}