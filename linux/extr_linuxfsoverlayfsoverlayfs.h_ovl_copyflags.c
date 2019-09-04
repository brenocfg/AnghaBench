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
struct inode {unsigned int i_flags; } ;

/* Variables and functions */
 unsigned int S_APPEND ; 
 unsigned int S_IMMUTABLE ; 
 unsigned int S_NOATIME ; 
 unsigned int S_SYNC ; 
 int /*<<< orphan*/  inode_set_flags (struct inode*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void ovl_copyflags(struct inode *from, struct inode *to)
{
	unsigned int mask = S_SYNC | S_IMMUTABLE | S_APPEND | S_NOATIME;

	inode_set_flags(to, from->i_flags & mask, mask);
}