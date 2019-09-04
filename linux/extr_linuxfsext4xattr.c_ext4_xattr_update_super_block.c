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
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_sbh; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext4_handle_dirty_super (int /*<<< orphan*/ *,struct super_block*) ; 
 scalar_t__ ext4_has_feature_xattr (struct super_block*) ; 
 scalar_t__ ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_set_feature_xattr (struct super_block*) ; 

__attribute__((used)) static void ext4_xattr_update_super_block(handle_t *handle,
					  struct super_block *sb)
{
	if (ext4_has_feature_xattr(sb))
		return;

	BUFFER_TRACE(EXT4_SB(sb)->s_sbh, "get_write_access");
	if (ext4_journal_get_write_access(handle, EXT4_SB(sb)->s_sbh) == 0) {
		ext4_set_feature_xattr(sb);
		ext4_handle_dirty_super(handle, sb);
	}
}