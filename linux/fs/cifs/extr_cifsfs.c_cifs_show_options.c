#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct seq_file {int dummy; } ;
struct dentry {TYPE_5__* d_sb; } ;
struct cifs_tcon {int snapshot_time; int handle_timeout; TYPE_3__* ses; scalar_t__ unix_ext; scalar_t__ posix_extensions; scalar_t__ use_resilient; scalar_t__ use_persistent; scalar_t__ retry; scalar_t__ local_lease; scalar_t__ nocase; scalar_t__ seal; scalar_t__ no_lease; } ;
struct cifs_sb_info {int mnt_cifs_flags; int rsize; int wsize; int bsize; int actimeo; int /*<<< orphan*/  mnt_backupgid; int /*<<< orphan*/  mnt_backupuid; int /*<<< orphan*/  local_nls; int /*<<< orphan*/  mnt_dir_mode; int /*<<< orphan*/  mnt_file_mode; int /*<<< orphan*/  mnt_gid; int /*<<< orphan*/  mnt_uid; } ;
struct TYPE_10__ {int s_flags; } ;
struct TYPE_9__ {int min_offload; int echo_interval; int max_credits; TYPE_1__* vals; int /*<<< orphan*/  srcaddr; } ;
struct TYPE_8__ {scalar_t__* user_name; scalar_t__* domainName; TYPE_4__* server; } ;
struct TYPE_6__ {scalar_t__* version_string; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int CIFS_MOUNT_CIFS_ACL ; 
 int CIFS_MOUNT_CIFS_BACKUPGID ; 
 int CIFS_MOUNT_CIFS_BACKUPUID ; 
 int CIFS_MOUNT_DYNPERM ; 
 int CIFS_MOUNT_FSCACHE ; 
 int CIFS_MOUNT_MAP_SFM_CHR ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int CIFS_MOUNT_MF_SYMLINKS ; 
 int CIFS_MOUNT_MODE_FROM_SID ; 
 int CIFS_MOUNT_MULTIUSER ; 
 int CIFS_MOUNT_NOPOSIXBRL ; 
 int CIFS_MOUNT_NOSSYNC ; 
 int CIFS_MOUNT_NO_BRL ; 
 int CIFS_MOUNT_NO_DFS ; 
 int CIFS_MOUNT_NO_HANDLE_CACHE ; 
 int CIFS_MOUNT_NO_PERM ; 
 int CIFS_MOUNT_NO_XATTR ; 
 int CIFS_MOUNT_OVERR_GID ; 
 int CIFS_MOUNT_OVERR_UID ; 
 int CIFS_MOUNT_POSIX_PATHS ; 
 int CIFS_MOUNT_RWPIDFORWARD ; 
 int CIFS_MOUNT_SERVER_INUM ; 
 int CIFS_MOUNT_SET_UID ; 
 int CIFS_MOUNT_UID_FROM_ACL ; 
 int CIFS_MOUNT_UNX_EMUL ; 
 struct cifs_sb_info* CIFS_SB (TYPE_5__*) ; 
 int HZ ; 
 int SB_POSIXACL ; 
 int SMB2_MAX_CREDITS_AVAILABLE ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_show_address (struct seq_file*,TYPE_4__*) ; 
 int /*<<< orphan*/  cifs_show_cache_flavor (struct seq_file*,struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_show_nls (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_show_security (struct seq_file*,TYPE_3__*) ; 
 int from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  seq_show_option (struct seq_file*,char*,scalar_t__*) ; 

__attribute__((used)) static int
cifs_show_options(struct seq_file *s, struct dentry *root)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(root->d_sb);
	struct cifs_tcon *tcon = cifs_sb_master_tcon(cifs_sb);
	struct sockaddr *srcaddr;
	srcaddr = (struct sockaddr *)&tcon->ses->server->srcaddr;

	seq_show_option(s, "vers", tcon->ses->server->vals->version_string);
	cifs_show_security(s, tcon->ses);
	cifs_show_cache_flavor(s, cifs_sb);

	if (tcon->no_lease)
		seq_puts(s, ",nolease");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MULTIUSER)
		seq_puts(s, ",multiuser");
	else if (tcon->ses->user_name)
		seq_show_option(s, "username", tcon->ses->user_name);

	if (tcon->ses->domainName && tcon->ses->domainName[0] != 0)
		seq_show_option(s, "domain", tcon->ses->domainName);

	if (srcaddr->sa_family != AF_UNSPEC) {
		struct sockaddr_in *saddr4;
		struct sockaddr_in6 *saddr6;
		saddr4 = (struct sockaddr_in *)srcaddr;
		saddr6 = (struct sockaddr_in6 *)srcaddr;
		if (srcaddr->sa_family == AF_INET6)
			seq_printf(s, ",srcaddr=%pI6c",
				   &saddr6->sin6_addr);
		else if (srcaddr->sa_family == AF_INET)
			seq_printf(s, ",srcaddr=%pI4",
				   &saddr4->sin_addr.s_addr);
		else
			seq_printf(s, ",srcaddr=BAD-AF:%i",
				   (int)(srcaddr->sa_family));
	}

	seq_printf(s, ",uid=%u",
		   from_kuid_munged(&init_user_ns, cifs_sb->mnt_uid));
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_OVERR_UID)
		seq_puts(s, ",forceuid");
	else
		seq_puts(s, ",noforceuid");

	seq_printf(s, ",gid=%u",
		   from_kgid_munged(&init_user_ns, cifs_sb->mnt_gid));
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_OVERR_GID)
		seq_puts(s, ",forcegid");
	else
		seq_puts(s, ",noforcegid");

	cifs_show_address(s, tcon->ses->server);

	if (!tcon->unix_ext)
		seq_printf(s, ",file_mode=0%ho,dir_mode=0%ho",
					   cifs_sb->mnt_file_mode,
					   cifs_sb->mnt_dir_mode);

	cifs_show_nls(s, cifs_sb->local_nls);

	if (tcon->seal)
		seq_puts(s, ",seal");
	if (tcon->nocase)
		seq_puts(s, ",nocase");
	if (tcon->local_lease)
		seq_puts(s, ",locallease");
	if (tcon->retry)
		seq_puts(s, ",hard");
	else
		seq_puts(s, ",soft");
	if (tcon->use_persistent)
		seq_puts(s, ",persistenthandles");
	else if (tcon->use_resilient)
		seq_puts(s, ",resilienthandles");
	if (tcon->posix_extensions)
		seq_puts(s, ",posix");
	else if (tcon->unix_ext)
		seq_puts(s, ",unix");
	else
		seq_puts(s, ",nounix");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_DFS)
		seq_puts(s, ",nodfs");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_POSIX_PATHS)
		seq_puts(s, ",posixpaths");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SET_UID)
		seq_puts(s, ",setuids");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_UID_FROM_ACL)
		seq_puts(s, ",idsfromsid");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM)
		seq_puts(s, ",serverino");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_RWPIDFORWARD)
		seq_puts(s, ",rwpidforward");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NOPOSIXBRL)
		seq_puts(s, ",forcemand");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_XATTR)
		seq_puts(s, ",nouser_xattr");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR)
		seq_puts(s, ",mapchars");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SFM_CHR)
		seq_puts(s, ",mapposix");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_UNX_EMUL)
		seq_puts(s, ",sfu");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_BRL)
		seq_puts(s, ",nobrl");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_HANDLE_CACHE)
		seq_puts(s, ",nohandlecache");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MODE_FROM_SID)
		seq_puts(s, ",modefromsid");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL)
		seq_puts(s, ",cifsacl");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DYNPERM)
		seq_puts(s, ",dynperm");
	if (root->d_sb->s_flags & SB_POSIXACL)
		seq_puts(s, ",acl");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS)
		seq_puts(s, ",mfsymlinks");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_FSCACHE)
		seq_puts(s, ",fsc");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NOSSYNC)
		seq_puts(s, ",nostrictsync");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_PERM)
		seq_puts(s, ",noperm");
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_BACKUPUID)
		seq_printf(s, ",backupuid=%u",
			   from_kuid_munged(&init_user_ns,
					    cifs_sb->mnt_backupuid));
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_BACKUPGID)
		seq_printf(s, ",backupgid=%u",
			   from_kgid_munged(&init_user_ns,
					    cifs_sb->mnt_backupgid));

	seq_printf(s, ",rsize=%u", cifs_sb->rsize);
	seq_printf(s, ",wsize=%u", cifs_sb->wsize);
	seq_printf(s, ",bsize=%u", cifs_sb->bsize);
	if (tcon->ses->server->min_offload)
		seq_printf(s, ",esize=%u", tcon->ses->server->min_offload);
	seq_printf(s, ",echo_interval=%lu",
			tcon->ses->server->echo_interval / HZ);

	/* Only display max_credits if it was overridden on mount */
	if (tcon->ses->server->max_credits != SMB2_MAX_CREDITS_AVAILABLE)
		seq_printf(s, ",max_credits=%u", tcon->ses->server->max_credits);

	if (tcon->snapshot_time)
		seq_printf(s, ",snapshot=%llu", tcon->snapshot_time);
	if (tcon->handle_timeout)
		seq_printf(s, ",handletimeout=%u", tcon->handle_timeout);
	/* convert actimeo and display it in seconds */
	seq_printf(s, ",actimeo=%lu", cifs_sb->actimeo / HZ);

	return 0;
}