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
typedef  int /*<<< orphan*/  u64 ;
struct send_ctx {int /*<<< orphan*/  parent_root; } ;
struct fs_path {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int ENOMEM ; 
 int did_overwrite_ref (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int /*<<< orphan*/  fs_path_len (struct fs_path*) ; 
 int get_first_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fs_path*) ; 

__attribute__((used)) static int did_overwrite_first_ref(struct send_ctx *sctx, u64 ino, u64 gen)
{
	int ret = 0;
	struct fs_path *name = NULL;
	u64 dir;
	u64 dir_gen;

	if (!sctx->parent_root)
		goto out;

	name = fs_path_alloc();
	if (!name)
		return -ENOMEM;

	ret = get_first_ref(sctx->parent_root, ino, &dir, &dir_gen, name);
	if (ret < 0)
		goto out;

	ret = did_overwrite_ref(sctx, dir, dir_gen, ino, gen,
			name->start, fs_path_len(name));

out:
	fs_path_free(name);
	return ret;
}