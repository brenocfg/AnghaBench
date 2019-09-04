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
struct f2fs_sb_info {int /*<<< orphan*/  s_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void set_sbi_flag(struct f2fs_sb_info *sbi, unsigned int type)
{
	set_bit(type, &sbi->s_flag);
}