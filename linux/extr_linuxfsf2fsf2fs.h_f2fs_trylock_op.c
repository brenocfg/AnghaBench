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
struct f2fs_sb_info {int /*<<< orphan*/  cp_rwsem; } ;

/* Variables and functions */
 int down_read_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int f2fs_trylock_op(struct f2fs_sb_info *sbi)
{
	return down_read_trylock(&sbi->cp_rwsem);
}