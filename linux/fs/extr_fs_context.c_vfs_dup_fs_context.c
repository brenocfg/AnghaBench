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
struct fs_context {TYPE_2__* ops; TYPE_1__* log; int /*<<< orphan*/  cred; int /*<<< orphan*/  user_ns; int /*<<< orphan*/  net_ns; int /*<<< orphan*/  fs_type; int /*<<< orphan*/ * security; int /*<<< orphan*/ * source; int /*<<< orphan*/ * s_fs_info; int /*<<< orphan*/ * fs_private; int /*<<< orphan*/  uapi_mutex; } ;
struct TYPE_4__ {int (* dup ) (struct fs_context*,struct fs_context*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct fs_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_filesystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_user_ns (int /*<<< orphan*/ ) ; 
 struct fs_context* kmemdup (struct fs_context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int security_fs_context_dup (struct fs_context*,struct fs_context*) ; 
 int stub1 (struct fs_context*,struct fs_context*) ; 

struct fs_context *vfs_dup_fs_context(struct fs_context *src_fc)
{
	struct fs_context *fc;
	int ret;

	if (!src_fc->ops->dup)
		return ERR_PTR(-EOPNOTSUPP);

	fc = kmemdup(src_fc, sizeof(struct fs_context), GFP_KERNEL);
	if (!fc)
		return ERR_PTR(-ENOMEM);

	mutex_init(&fc->uapi_mutex);

	fc->fs_private	= NULL;
	fc->s_fs_info	= NULL;
	fc->source	= NULL;
	fc->security	= NULL;
	get_filesystem(fc->fs_type);
	get_net(fc->net_ns);
	get_user_ns(fc->user_ns);
	get_cred(fc->cred);
	if (fc->log)
		refcount_inc(&fc->log->usage);

	/* Can't call put until we've called ->dup */
	ret = fc->ops->dup(fc, src_fc);
	if (ret < 0)
		goto err_fc;

	ret = security_fs_context_dup(fc, src_fc);
	if (ret < 0)
		goto err_fc;
	return fc;

err_fc:
	put_fs_context(fc);
	return ERR_PTR(ret);
}