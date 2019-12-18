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
struct seq_file {size_t count; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct ceph_mount_options {int flags; char* fscache_uniq; int sb_flags; char* mds_namespace; scalar_t__ wsize; scalar_t__ rsize; scalar_t__ rasize; scalar_t__ congestion_kb; scalar_t__ caps_max; scalar_t__ caps_wanted_delay_min; scalar_t__ caps_wanted_delay_max; scalar_t__ max_readdir; scalar_t__ max_readdir_bytes; char* snapdir_name; } ;
struct ceph_fs_client {int /*<<< orphan*/  client; struct ceph_mount_options* mount_options; } ;

/* Variables and functions */
 scalar_t__ CEPH_CAPS_WANTED_DELAY_MAX_DEFAULT ; 
 scalar_t__ CEPH_CAPS_WANTED_DELAY_MIN_DEFAULT ; 
 scalar_t__ CEPH_MAX_READDIR_BYTES_DEFAULT ; 
 scalar_t__ CEPH_MAX_READDIR_DEFAULT ; 
 scalar_t__ CEPH_MAX_READ_SIZE ; 
 scalar_t__ CEPH_MAX_WRITE_SIZE ; 
 int CEPH_MOUNT_OPT_CLEANRECOVER ; 
 int CEPH_MOUNT_OPT_DCACHE ; 
 int CEPH_MOUNT_OPT_DIRSTAT ; 
 int CEPH_MOUNT_OPT_FSCACHE ; 
 int CEPH_MOUNT_OPT_INO32 ; 
 int CEPH_MOUNT_OPT_NOASYNCREADDIR ; 
 int CEPH_MOUNT_OPT_NOCOPYFROM ; 
 int CEPH_MOUNT_OPT_NOPOOLPERM ; 
 int CEPH_MOUNT_OPT_NOQUOTADF ; 
 int CEPH_MOUNT_OPT_RBYTES ; 
 scalar_t__ CEPH_RASIZE_DEFAULT ; 
 int /*<<< orphan*/  CEPH_SNAPDIRNAME_DEFAULT ; 
 int SB_POSIXACL ; 
 int ceph_print_client_options (struct seq_file*,int /*<<< orphan*/ ,int) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 scalar_t__ default_congestion_kb () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  seq_show_option (struct seq_file*,char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_show_options(struct seq_file *m, struct dentry *root)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(root->d_sb);
	struct ceph_mount_options *fsopt = fsc->mount_options;
	size_t pos;
	int ret;

	/* a comma between MNT/MS and client options */
	seq_putc(m, ',');
	pos = m->count;

	ret = ceph_print_client_options(m, fsc->client, false);
	if (ret)
		return ret;

	/* retract our comma if no client options */
	if (m->count == pos)
		m->count--;

	if (fsopt->flags & CEPH_MOUNT_OPT_DIRSTAT)
		seq_puts(m, ",dirstat");
	if ((fsopt->flags & CEPH_MOUNT_OPT_RBYTES))
		seq_puts(m, ",rbytes");
	if (fsopt->flags & CEPH_MOUNT_OPT_NOASYNCREADDIR)
		seq_puts(m, ",noasyncreaddir");
	if ((fsopt->flags & CEPH_MOUNT_OPT_DCACHE) == 0)
		seq_puts(m, ",nodcache");
	if (fsopt->flags & CEPH_MOUNT_OPT_INO32)
		seq_puts(m, ",ino32");
	if (fsopt->flags & CEPH_MOUNT_OPT_FSCACHE) {
		seq_show_option(m, "fsc", fsopt->fscache_uniq);
	}
	if (fsopt->flags & CEPH_MOUNT_OPT_NOPOOLPERM)
		seq_puts(m, ",nopoolperm");
	if (fsopt->flags & CEPH_MOUNT_OPT_NOQUOTADF)
		seq_puts(m, ",noquotadf");

#ifdef CONFIG_CEPH_FS_POSIX_ACL
	if (fsopt->sb_flags & SB_POSIXACL)
		seq_puts(m, ",acl");
	else
		seq_puts(m, ",noacl");
#endif

	if ((fsopt->flags & CEPH_MOUNT_OPT_NOCOPYFROM) == 0)
		seq_puts(m, ",copyfrom");

	if (fsopt->mds_namespace)
		seq_show_option(m, "mds_namespace", fsopt->mds_namespace);

	if (fsopt->flags & CEPH_MOUNT_OPT_CLEANRECOVER)
		seq_show_option(m, "recover_session", "clean");

	if (fsopt->wsize != CEPH_MAX_WRITE_SIZE)
		seq_printf(m, ",wsize=%d", fsopt->wsize);
	if (fsopt->rsize != CEPH_MAX_READ_SIZE)
		seq_printf(m, ",rsize=%d", fsopt->rsize);
	if (fsopt->rasize != CEPH_RASIZE_DEFAULT)
		seq_printf(m, ",rasize=%d", fsopt->rasize);
	if (fsopt->congestion_kb != default_congestion_kb())
		seq_printf(m, ",write_congestion_kb=%d", fsopt->congestion_kb);
	if (fsopt->caps_max)
		seq_printf(m, ",caps_max=%d", fsopt->caps_max);
	if (fsopt->caps_wanted_delay_min != CEPH_CAPS_WANTED_DELAY_MIN_DEFAULT)
		seq_printf(m, ",caps_wanted_delay_min=%d",
			 fsopt->caps_wanted_delay_min);
	if (fsopt->caps_wanted_delay_max != CEPH_CAPS_WANTED_DELAY_MAX_DEFAULT)
		seq_printf(m, ",caps_wanted_delay_max=%d",
			   fsopt->caps_wanted_delay_max);
	if (fsopt->max_readdir != CEPH_MAX_READDIR_DEFAULT)
		seq_printf(m, ",readdir_max_entries=%d", fsopt->max_readdir);
	if (fsopt->max_readdir_bytes != CEPH_MAX_READDIR_BYTES_DEFAULT)
		seq_printf(m, ",readdir_max_bytes=%d", fsopt->max_readdir_bytes);
	if (strcmp(fsopt->snapdir_name, CEPH_SNAPDIRNAME_DEFAULT))
		seq_show_option(m, "snapdirname", fsopt->snapdir_name);

	return 0;
}