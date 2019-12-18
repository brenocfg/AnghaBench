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
struct gfs2_args {int ar_commit; int ar_statfs_quantum; int ar_quota_quantum; int /*<<< orphan*/  ar_errors; int /*<<< orphan*/  ar_data; int /*<<< orphan*/  ar_quota; } ;
struct gfs2_sbd {struct gfs2_args sd_args; } ;
struct fs_context {scalar_t__ purpose; int /*<<< orphan*/ * ops; struct gfs2_args* fs_private; TYPE_2__* root; } ;
struct TYPE_4__ {TYPE_1__* d_sb; } ;
struct TYPE_3__ {struct gfs2_sbd* s_fs_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FS_CONTEXT_FOR_RECONFIGURE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFS2_DATA_DEFAULT ; 
 int /*<<< orphan*/  GFS2_ERRORS_DEFAULT ; 
 int /*<<< orphan*/  GFS2_QUOTA_DEFAULT ; 
 int /*<<< orphan*/  gfs2_context_ops ; 
 struct gfs2_args* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct gfs2_args*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfs2_init_fs_context(struct fs_context *fc)
{
	struct gfs2_args *args;

	args = kmalloc(sizeof(*args), GFP_KERNEL);
	if (args == NULL)
		return -ENOMEM;

	if (fc->purpose == FS_CONTEXT_FOR_RECONFIGURE) {
		struct gfs2_sbd *sdp = fc->root->d_sb->s_fs_info;

		*args = sdp->sd_args;
	} else {
		memset(args, 0, sizeof(*args));
		args->ar_quota = GFS2_QUOTA_DEFAULT;
		args->ar_data = GFS2_DATA_DEFAULT;
		args->ar_commit = 30;
		args->ar_statfs_quantum = 30;
		args->ar_quota_quantum = 60;
		args->ar_errors = GFS2_ERRORS_DEFAULT;
	}
	fc->fs_private = args;
	fc->ops = &gfs2_context_ops;
	return 0;
}