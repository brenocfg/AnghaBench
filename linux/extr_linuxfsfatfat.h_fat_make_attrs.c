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
typedef  int /*<<< orphan*/  u8 ;
struct inode {int i_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_DIR ; 
 int /*<<< orphan*/  ATTR_RO ; 
 TYPE_1__* MSDOS_I (struct inode*) ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_IWUGO ; 
 scalar_t__ fat_mode_can_hold_ro (struct inode*) ; 

__attribute__((used)) static inline u8 fat_make_attrs(struct inode *inode)
{
	u8 attrs = MSDOS_I(inode)->i_attrs;
	if (S_ISDIR(inode->i_mode))
		attrs |= ATTR_DIR;
	if (fat_mode_can_hold_ro(inode) && !(inode->i_mode & S_IWUGO))
		attrs |= ATTR_RO;
	return attrs;
}