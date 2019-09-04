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
struct send_ctx {int dummy; } ;
struct fs_path {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int gen_unique_name (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int send_rename (struct send_ctx*,struct fs_path*,struct fs_path*) ; 

__attribute__((used)) static int orphanize_inode(struct send_ctx *sctx, u64 ino, u64 gen,
			  struct fs_path *path)
{
	int ret;
	struct fs_path *orphan;

	orphan = fs_path_alloc();
	if (!orphan)
		return -ENOMEM;

	ret = gen_unique_name(sctx, ino, gen, orphan);
	if (ret < 0)
		goto out;

	ret = send_rename(sctx, path, orphan);

out:
	fs_path_free(orphan);
	return ret;
}