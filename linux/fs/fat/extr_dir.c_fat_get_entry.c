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
struct msdos_dir_entry {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int loff_t ;
struct TYPE_2__ {int dir_per_block; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int fat__get_entry (struct inode*,int*,struct buffer_head**,struct msdos_dir_entry**) ; 

__attribute__((used)) static inline int fat_get_entry(struct inode *dir, loff_t *pos,
				struct buffer_head **bh,
				struct msdos_dir_entry **de)
{
	/* Fast stuff first */
	if (*bh && *de &&
	   (*de - (struct msdos_dir_entry *)(*bh)->b_data) <
				MSDOS_SB(dir->i_sb)->dir_per_block - 1) {
		*pos += sizeof(struct msdos_dir_entry);
		(*de)++;
		return 0;
	}
	return fat__get_entry(dir, pos, bh, de);
}