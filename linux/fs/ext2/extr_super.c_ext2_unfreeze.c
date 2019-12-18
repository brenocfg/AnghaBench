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
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2_write_super (struct super_block*) ; 

__attribute__((used)) static int ext2_unfreeze(struct super_block *sb)
{
	/* Just write sb to clear EXT2_VALID_FS flag */
	ext2_write_super(sb);

	return 0;
}