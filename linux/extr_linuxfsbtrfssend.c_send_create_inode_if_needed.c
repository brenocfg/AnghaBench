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
struct send_ctx {int /*<<< orphan*/  cur_ino; int /*<<< orphan*/  cur_inode_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int did_create_dir (struct send_ctx*,int /*<<< orphan*/ ) ; 
 int send_create_inode (struct send_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_create_inode_if_needed(struct send_ctx *sctx)
{
	int ret;

	if (S_ISDIR(sctx->cur_inode_mode)) {
		ret = did_create_dir(sctx, sctx->cur_ino);
		if (ret < 0)
			goto out;
		if (ret) {
			ret = 0;
			goto out;
		}
	}

	ret = send_create_inode(sctx, sctx->cur_ino);
	if (ret < 0)
		goto out;

out:
	return ret;
}