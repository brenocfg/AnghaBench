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
typedef  int u8 ;
struct TYPE_2__ {int** ent12_p; } ;
struct fat_entry {int entry; int nr_bhs; int /*<<< orphan*/  fat_inode; int /*<<< orphan*/ * bhs; TYPE_1__ u; } ;

/* Variables and functions */
 int EOF_FAT12 ; 
 int FAT_ENT_EOF ; 
 int /*<<< orphan*/  fat12_entry_lock ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fat12_ent_put(struct fat_entry *fatent, int new)
{
	u8 **ent12_p = fatent->u.ent12_p;

	if (new == FAT_ENT_EOF)
		new = EOF_FAT12;

	spin_lock(&fat12_entry_lock);
	if (fatent->entry & 1) {
		*ent12_p[0] = (new << 4) | (*ent12_p[0] & 0x0f);
		*ent12_p[1] = new >> 4;
	} else {
		*ent12_p[0] = new & 0xff;
		*ent12_p[1] = (*ent12_p[1] & 0xf0) | (new >> 8);
	}
	spin_unlock(&fat12_entry_lock);

	mark_buffer_dirty_inode(fatent->bhs[0], fatent->fat_inode);
	if (fatent->nr_bhs == 2)
		mark_buffer_dirty_inode(fatent->bhs[1], fatent->fat_inode);
}