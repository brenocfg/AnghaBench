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
struct ext4_sb_info {int /*<<< orphan*/  s_ext4_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FLAGS_SHUTDOWN ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ext4_forced_shutdown(struct ext4_sb_info *sbi)
{
	return test_bit(EXT4_FLAGS_SHUTDOWN, &sbi->s_ext4_flags);
}