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
struct ocxlflash_context {int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocxlflash_fs_cnt ; 
 int /*<<< orphan*/  ocxlflash_vfs_mount ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocxlflash_release_mapping(struct ocxlflash_context *ctx)
{
	if (ctx->mapping)
		simple_release_fs(&ocxlflash_vfs_mount, &ocxlflash_fs_cnt);
	ctx->mapping = NULL;
}