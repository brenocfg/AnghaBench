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
struct send_ctx {int dummy; } ;
struct recorded_ref {struct fs_path* full_path; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; int /*<<< orphan*/  dir_gen; int /*<<< orphan*/  dir; } ;
struct fs_path {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int fs_path_add (struct fs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int get_cur_path (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int /*<<< orphan*/  set_ref_path (struct recorded_ref*,struct fs_path*) ; 

__attribute__((used)) static int update_ref_path(struct send_ctx *sctx, struct recorded_ref *ref)
{
	int ret;
	struct fs_path *new_path;

	/*
	 * Our reference's name member points to its full_path member string, so
	 * we use here a new path.
	 */
	new_path = fs_path_alloc();
	if (!new_path)
		return -ENOMEM;

	ret = get_cur_path(sctx, ref->dir, ref->dir_gen, new_path);
	if (ret < 0) {
		fs_path_free(new_path);
		return ret;
	}
	ret = fs_path_add(new_path, ref->name, ref->name_len);
	if (ret < 0) {
		fs_path_free(new_path);
		return ret;
	}

	fs_path_free(ref->full_path);
	set_ref_path(ref, new_path);

	return 0;
}