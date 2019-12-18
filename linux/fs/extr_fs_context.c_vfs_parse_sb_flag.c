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
struct fs_context {unsigned int sb_flags; unsigned int sb_flags_mask; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOPARAM ; 
 int /*<<< orphan*/  common_clear_sb_flag ; 
 int /*<<< orphan*/  common_set_sb_flag ; 
 int /*<<< orphan*/ * forbidden_sb_flag ; 
 unsigned int lookup_constant (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfs_parse_sb_flag(struct fs_context *fc, const char *key)
{
	unsigned int token;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(forbidden_sb_flag); i++)
		if (strcmp(key, forbidden_sb_flag[i]) == 0)
			return -EINVAL;

	token = lookup_constant(common_set_sb_flag, key, 0);
	if (token) {
		fc->sb_flags |= token;
		fc->sb_flags_mask |= token;
		return 0;
	}

	token = lookup_constant(common_clear_sb_flag, key, 0);
	if (token) {
		fc->sb_flags &= ~token;
		fc->sb_flags_mask |= token;
		return 0;
	}

	return -ENOPARAM;
}