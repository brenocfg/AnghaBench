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
struct fs_context {int /*<<< orphan*/  sb_flags; TYPE_1__* root; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  sync_filesystem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int romfs_reconfigure(struct fs_context *fc)
{
	sync_filesystem(fc->root->d_sb);
	fc->sb_flags |= SB_RDONLY;
	return 0;
}