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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct TYPE_2__ {int i_flags; } ;

/* Variables and functions */
 int EXT4_EA_INODE_FL ; 
 TYPE_1__* EXT4_I (struct inode const*) ; 
 int /*<<< orphan*/  inode_peek_iversion (struct inode const*) ; 
 int /*<<< orphan*/  inode_peek_iversion_raw (struct inode const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u64 ext4_inode_peek_iversion(const struct inode *inode)
{
	if (unlikely(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL))
		return inode_peek_iversion_raw(inode);
	else
		return inode_peek_iversion(inode);
}