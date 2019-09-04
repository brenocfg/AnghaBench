#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_dev {int dummy; } ;
struct file {struct fuse_dev* private_data; TYPE_1__* f_cred; } ;
struct TYPE_5__ {int initialized; int /*<<< orphan*/  release; } ;
struct cuse_conn {TYPE_2__ fc; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cuse_fc_release ; 
 int cuse_send_init (struct cuse_conn*) ; 
 int /*<<< orphan*/  fuse_conn_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct fuse_dev* fuse_dev_alloc (TYPE_2__*) ; 
 int /*<<< orphan*/  fuse_dev_free (struct fuse_dev*) ; 
 int /*<<< orphan*/  kfree (struct cuse_conn*) ; 
 struct cuse_conn* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cuse_channel_open(struct inode *inode, struct file *file)
{
	struct fuse_dev *fud;
	struct cuse_conn *cc;
	int rc;

	/* set up cuse_conn */
	cc = kzalloc(sizeof(*cc), GFP_KERNEL);
	if (!cc)
		return -ENOMEM;

	/*
	 * Limit the cuse channel to requests that can
	 * be represented in file->f_cred->user_ns.
	 */
	fuse_conn_init(&cc->fc, file->f_cred->user_ns);

	fud = fuse_dev_alloc(&cc->fc);
	if (!fud) {
		kfree(cc);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&cc->list);
	cc->fc.release = cuse_fc_release;

	cc->fc.initialized = 1;
	rc = cuse_send_init(cc);
	if (rc) {
		fuse_dev_free(fud);
		return rc;
	}
	file->private_data = fud;

	return 0;
}