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
struct fat_entry {int entry; TYPE_1__ u; } ;

/* Variables and functions */
 int BAD_FAT12 ; 
 int FAT_ENT_EOF ; 
 int /*<<< orphan*/  fat12_entry_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fat12_ent_get(struct fat_entry *fatent)
{
	u8 **ent12_p = fatent->u.ent12_p;
	int next;

	spin_lock(&fat12_entry_lock);
	if (fatent->entry & 1)
		next = (*ent12_p[0] >> 4) | (*ent12_p[1] << 4);
	else
		next = (*ent12_p[1] << 8) | *ent12_p[0];
	spin_unlock(&fat12_entry_lock);

	next &= 0x0fff;
	if (next >= BAD_FAT12)
		next = FAT_ENT_EOF;
	return next;
}