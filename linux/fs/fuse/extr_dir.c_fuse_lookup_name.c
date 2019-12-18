#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
struct qstr {scalar_t__ len; } ;
struct inode {int dummy; } ;
struct fuse_forget_link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct fuse_entry_out {int /*<<< orphan*/  nodeid; TYPE_1__ attr; int /*<<< orphan*/  generation; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUSE_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ FUSE_NAME_MAX ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  entry_attr_timeout (struct fuse_entry_out*) ; 
 struct fuse_forget_link* fuse_alloc_forget () ; 
 int /*<<< orphan*/  fuse_get_attr_version (struct fuse_conn*) ; 
 struct inode* fuse_iget (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_lookup_init (struct fuse_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct qstr const*,struct fuse_entry_out*) ; 
 int /*<<< orphan*/  fuse_queue_forget (struct fuse_conn*,struct fuse_forget_link*,int /*<<< orphan*/ ,int) ; 
 int fuse_simple_request (struct fuse_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_valid_type (int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct fuse_forget_link*) ; 

int fuse_lookup_name(struct super_block *sb, u64 nodeid, const struct qstr *name,
		     struct fuse_entry_out *outarg, struct inode **inode)
{
	struct fuse_conn *fc = get_fuse_conn_super(sb);
	FUSE_ARGS(args);
	struct fuse_forget_link *forget;
	u64 attr_version;
	int err;

	*inode = NULL;
	err = -ENAMETOOLONG;
	if (name->len > FUSE_NAME_MAX)
		goto out;


	forget = fuse_alloc_forget();
	err = -ENOMEM;
	if (!forget)
		goto out;

	attr_version = fuse_get_attr_version(fc);

	fuse_lookup_init(fc, &args, nodeid, name, outarg);
	err = fuse_simple_request(fc, &args);
	/* Zero nodeid is same as -ENOENT, but with valid timeout */
	if (err || !outarg->nodeid)
		goto out_put_forget;

	err = -EIO;
	if (!outarg->nodeid)
		goto out_put_forget;
	if (!fuse_valid_type(outarg->attr.mode))
		goto out_put_forget;

	*inode = fuse_iget(sb, outarg->nodeid, outarg->generation,
			   &outarg->attr, entry_attr_timeout(outarg),
			   attr_version);
	err = -ENOMEM;
	if (!*inode) {
		fuse_queue_forget(fc, forget, outarg->nodeid, 1);
		goto out;
	}
	err = 0;

 out_put_forget:
	kfree(forget);
 out:
	return err;
}