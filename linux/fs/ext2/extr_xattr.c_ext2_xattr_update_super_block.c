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
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_sbh; int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_FEATURE_COMPAT_EXT_ATTR ; 
 scalar_t__ EXT2_HAS_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT2_SET_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_update_dynamic_rev (struct super_block*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext2_xattr_update_super_block(struct super_block *sb)
{
	if (EXT2_HAS_COMPAT_FEATURE(sb, EXT2_FEATURE_COMPAT_EXT_ATTR))
		return;

	spin_lock(&EXT2_SB(sb)->s_lock);
	ext2_update_dynamic_rev(sb);
	EXT2_SET_COMPAT_FEATURE(sb, EXT2_FEATURE_COMPAT_EXT_ATTR);
	spin_unlock(&EXT2_SB(sb)->s_lock);
	mark_buffer_dirty(EXT2_SB(sb)->s_sbh);
}