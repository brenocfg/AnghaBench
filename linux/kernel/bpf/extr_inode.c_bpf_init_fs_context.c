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
struct fs_context {int /*<<< orphan*/ * ops; struct bpf_mount_opts* fs_private; } ;
struct bpf_mount_opts {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_IRWXUGO ; 
 int /*<<< orphan*/  bpf_context_ops ; 
 struct bpf_mount_opts* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_init_fs_context(struct fs_context *fc)
{
	struct bpf_mount_opts *opts;

	opts = kzalloc(sizeof(struct bpf_mount_opts), GFP_KERNEL);
	if (!opts)
		return -ENOMEM;

	opts->mode = S_IRWXUGO;

	fc->fs_private = opts;
	fc->ops = &bpf_context_ops;
	return 0;
}