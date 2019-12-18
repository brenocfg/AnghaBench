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
struct v9fs_session_info {int cache; int flags; int /*<<< orphan*/  clnt; int /*<<< orphan*/  uid; scalar_t__ cachetag; scalar_t__ nodev; scalar_t__ aname; scalar_t__ uname; scalar_t__ afid; int /*<<< orphan*/  dfltgid; int /*<<< orphan*/  dfltuid; scalar_t__ debug; } ;
struct seq_file {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct v9fs_session_info* s_fs_info; } ;

/* Variables and functions */
 size_t CACHE_FSCACHE ; 
#define  V9FS_ACCESS_ANY 131 
#define  V9FS_ACCESS_CLIENT 130 
 int V9FS_ACCESS_MASK ; 
#define  V9FS_ACCESS_SINGLE 129 
#define  V9FS_ACCESS_USER 128 
 int /*<<< orphan*/  V9FS_DEFANAME ; 
 int /*<<< orphan*/  V9FS_DEFGID ; 
 int /*<<< orphan*/  V9FS_DEFUID ; 
 int /*<<< orphan*/  V9FS_DEFUSER ; 
 int V9FS_POSIX_ACL ; 
 scalar_t__ from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int p9_show_client_options (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* v9fs_cache_modes ; 

int v9fs_show_options(struct seq_file *m, struct dentry *root)
{
	struct v9fs_session_info *v9ses = root->d_sb->s_fs_info;

	if (v9ses->debug)
		seq_printf(m, ",debug=%x", v9ses->debug);
	if (!uid_eq(v9ses->dfltuid, V9FS_DEFUID))
		seq_printf(m, ",dfltuid=%u",
			   from_kuid_munged(&init_user_ns, v9ses->dfltuid));
	if (!gid_eq(v9ses->dfltgid, V9FS_DEFGID))
		seq_printf(m, ",dfltgid=%u",
			   from_kgid_munged(&init_user_ns, v9ses->dfltgid));
	if (v9ses->afid != ~0)
		seq_printf(m, ",afid=%u", v9ses->afid);
	if (strcmp(v9ses->uname, V9FS_DEFUSER) != 0)
		seq_printf(m, ",uname=%s", v9ses->uname);
	if (strcmp(v9ses->aname, V9FS_DEFANAME) != 0)
		seq_printf(m, ",aname=%s", v9ses->aname);
	if (v9ses->nodev)
		seq_puts(m, ",nodevmap");
	if (v9ses->cache)
		seq_printf(m, ",%s", v9fs_cache_modes[v9ses->cache]);
#ifdef CONFIG_9P_FSCACHE
	if (v9ses->cachetag && v9ses->cache == CACHE_FSCACHE)
		seq_printf(m, ",cachetag=%s", v9ses->cachetag);
#endif

	switch (v9ses->flags & V9FS_ACCESS_MASK) {
	case V9FS_ACCESS_USER:
		seq_puts(m, ",access=user");
		break;
	case V9FS_ACCESS_ANY:
		seq_puts(m, ",access=any");
		break;
	case V9FS_ACCESS_CLIENT:
		seq_puts(m, ",access=client");
		break;
	case V9FS_ACCESS_SINGLE:
		seq_printf(m, ",access=%u",
			   from_kuid_munged(&init_user_ns, v9ses->uid));
		break;
	}

	if (v9ses->flags & V9FS_POSIX_ACL)
		seq_puts(m, ",posixacl");

	return p9_show_client_options(m, v9ses->clnt);
}