#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct TYPE_3__ {int /*<<< orphan*/ * iocharset; } ;
struct TYPE_4__ {int /*<<< orphan*/  nls; TYPE_1__ mount_opts; } ;

/* Variables and functions */
 TYPE_2__* BEFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
befs_put_super(struct super_block *sb)
{
	kfree(BEFS_SB(sb)->mount_opts.iocharset);
	BEFS_SB(sb)->mount_opts.iocharset = NULL;
	unload_nls(BEFS_SB(sb)->nls);
	kfree(sb->s_fs_info);
	sb->s_fs_info = NULL;
}