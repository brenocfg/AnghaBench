#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  from; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ substring_t ;
struct ceph_mount_options {int caps_wanted_delay_min; int caps_wanted_delay_max; int caps_max; int max_readdir; int max_readdir_bytes; int congestion_kb; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fscache_uniq; void* rasize; void* rsize; void* wsize; int /*<<< orphan*/ * mds_namespace; int /*<<< orphan*/ * snapdir_name; } ;

/* Variables and functions */
 void* ALIGN (int,scalar_t__) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CEPH_MAX_READ_SIZE ; 
 int CEPH_MAX_WRITE_SIZE ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_CLEANRECOVER ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_DCACHE ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_DIRSTAT ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_FSCACHE ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_INO32 ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_MOUNTWAIT ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_NOASYNCREADDIR ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_NOCOPYFROM ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_NOPOOLPERM ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_NOQUOTADF ; 
 int /*<<< orphan*/  CEPH_MOUNT_OPT_RBYTES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_acl 162 
#define  Opt_asyncreaddir 161 
#define  Opt_caps_max 160 
#define  Opt_caps_wanted_delay_max 159 
#define  Opt_caps_wanted_delay_min 158 
#define  Opt_congestion_kb 157 
#define  Opt_copyfrom 156 
#define  Opt_dcache 155 
#define  Opt_dirstat 154 
#define  Opt_fscache 153 
#define  Opt_fscache_uniq 152 
#define  Opt_ino32 151 
 int Opt_last_int ; 
 int Opt_last_string ; 
#define  Opt_mds_namespace 150 
#define  Opt_noacl 149 
#define  Opt_noasyncreaddir 148 
#define  Opt_nocopyfrom 147 
#define  Opt_nodcache 146 
#define  Opt_nodirstat 145 
#define  Opt_nofscache 144 
#define  Opt_noino32 143 
#define  Opt_nopoolperm 142 
#define  Opt_noquotadf 141 
#define  Opt_norbytes 140 
#define  Opt_norequire_active_mds 139 
#define  Opt_poolperm 138 
#define  Opt_quotadf 137 
#define  Opt_rasize 136 
#define  Opt_rbytes 135 
#define  Opt_readdir_max_bytes 134 
#define  Opt_readdir_max_entries 133 
#define  Opt_recover_session 132 
#define  Opt_require_active_mds 131 
#define  Opt_rsize 130 
#define  Opt_snapdirname 129 
#define  Opt_wsize 128 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SB_POSIXACL ; 
 int /*<<< orphan*/  dout (char*,int,...) ; 
 int /*<<< orphan*/  fsopt_tokens ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kstrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int match_int (TYPE_1__*,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_fsopt_token(char *c, void *private)
{
	struct ceph_mount_options *fsopt = private;
	substring_t argstr[MAX_OPT_ARGS];
	int token, intval, ret;

	token = match_token((char *)c, fsopt_tokens, argstr);
	if (token < 0)
		return -EINVAL;

	if (token < Opt_last_int) {
		ret = match_int(&argstr[0], &intval);
		if (ret < 0) {
			pr_err("bad option arg (not int) at '%s'\n", c);
			return ret;
		}
		dout("got int token %d val %d\n", token, intval);
	} else if (token > Opt_last_int && token < Opt_last_string) {
		dout("got string token %d val %s\n", token,
		     argstr[0].from);
	} else {
		dout("got token %d\n", token);
	}

	switch (token) {
	case Opt_snapdirname:
		kfree(fsopt->snapdir_name);
		fsopt->snapdir_name = kstrndup(argstr[0].from,
					       argstr[0].to-argstr[0].from,
					       GFP_KERNEL);
		if (!fsopt->snapdir_name)
			return -ENOMEM;
		break;
	case Opt_mds_namespace:
		kfree(fsopt->mds_namespace);
		fsopt->mds_namespace = kstrndup(argstr[0].from,
						argstr[0].to-argstr[0].from,
						GFP_KERNEL);
		if (!fsopt->mds_namespace)
			return -ENOMEM;
		break;
	case Opt_recover_session:
		if (!strncmp(argstr[0].from, "no",
			     argstr[0].to - argstr[0].from)) {
			fsopt->flags &= ~CEPH_MOUNT_OPT_CLEANRECOVER;
		} else if (!strncmp(argstr[0].from, "clean",
				    argstr[0].to - argstr[0].from)) {
			fsopt->flags |= CEPH_MOUNT_OPT_CLEANRECOVER;
		} else {
			return -EINVAL;
		}
		break;
	case Opt_fscache_uniq:
#ifdef CONFIG_CEPH_FSCACHE
		kfree(fsopt->fscache_uniq);
		fsopt->fscache_uniq = kstrndup(argstr[0].from,
					       argstr[0].to-argstr[0].from,
					       GFP_KERNEL);
		if (!fsopt->fscache_uniq)
			return -ENOMEM;
		fsopt->flags |= CEPH_MOUNT_OPT_FSCACHE;
		break;
#else
		pr_err("fscache support is disabled\n");
		return -EINVAL;
#endif
	case Opt_wsize:
		if (intval < (int)PAGE_SIZE || intval > CEPH_MAX_WRITE_SIZE)
			return -EINVAL;
		fsopt->wsize = ALIGN(intval, PAGE_SIZE);
		break;
	case Opt_rsize:
		if (intval < (int)PAGE_SIZE || intval > CEPH_MAX_READ_SIZE)
			return -EINVAL;
		fsopt->rsize = ALIGN(intval, PAGE_SIZE);
		break;
	case Opt_rasize:
		if (intval < 0)
			return -EINVAL;
		fsopt->rasize = ALIGN(intval, PAGE_SIZE);
		break;
	case Opt_caps_wanted_delay_min:
		if (intval < 1)
			return -EINVAL;
		fsopt->caps_wanted_delay_min = intval;
		break;
	case Opt_caps_wanted_delay_max:
		if (intval < 1)
			return -EINVAL;
		fsopt->caps_wanted_delay_max = intval;
		break;
	case Opt_caps_max:
		if (intval < 0)
			return -EINVAL;
		fsopt->caps_max = intval;
		break;
	case Opt_readdir_max_entries:
		if (intval < 1)
			return -EINVAL;
		fsopt->max_readdir = intval;
		break;
	case Opt_readdir_max_bytes:
		if (intval < (int)PAGE_SIZE && intval != 0)
			return -EINVAL;
		fsopt->max_readdir_bytes = intval;
		break;
	case Opt_congestion_kb:
		if (intval < 1024) /* at least 1M */
			return -EINVAL;
		fsopt->congestion_kb = intval;
		break;
	case Opt_dirstat:
		fsopt->flags |= CEPH_MOUNT_OPT_DIRSTAT;
		break;
	case Opt_nodirstat:
		fsopt->flags &= ~CEPH_MOUNT_OPT_DIRSTAT;
		break;
	case Opt_rbytes:
		fsopt->flags |= CEPH_MOUNT_OPT_RBYTES;
		break;
	case Opt_norbytes:
		fsopt->flags &= ~CEPH_MOUNT_OPT_RBYTES;
		break;
	case Opt_asyncreaddir:
		fsopt->flags &= ~CEPH_MOUNT_OPT_NOASYNCREADDIR;
		break;
	case Opt_noasyncreaddir:
		fsopt->flags |= CEPH_MOUNT_OPT_NOASYNCREADDIR;
		break;
	case Opt_dcache:
		fsopt->flags |= CEPH_MOUNT_OPT_DCACHE;
		break;
	case Opt_nodcache:
		fsopt->flags &= ~CEPH_MOUNT_OPT_DCACHE;
		break;
	case Opt_ino32:
		fsopt->flags |= CEPH_MOUNT_OPT_INO32;
		break;
	case Opt_noino32:
		fsopt->flags &= ~CEPH_MOUNT_OPT_INO32;
		break;
	case Opt_fscache:
#ifdef CONFIG_CEPH_FSCACHE
		fsopt->flags |= CEPH_MOUNT_OPT_FSCACHE;
		kfree(fsopt->fscache_uniq);
		fsopt->fscache_uniq = NULL;
		break;
#else
		pr_err("fscache support is disabled\n");
		return -EINVAL;
#endif
	case Opt_nofscache:
		fsopt->flags &= ~CEPH_MOUNT_OPT_FSCACHE;
		kfree(fsopt->fscache_uniq);
		fsopt->fscache_uniq = NULL;
		break;
	case Opt_poolperm:
		fsopt->flags &= ~CEPH_MOUNT_OPT_NOPOOLPERM;
		break;
	case Opt_nopoolperm:
		fsopt->flags |= CEPH_MOUNT_OPT_NOPOOLPERM;
		break;
	case Opt_require_active_mds:
		fsopt->flags &= ~CEPH_MOUNT_OPT_MOUNTWAIT;
		break;
	case Opt_norequire_active_mds:
		fsopt->flags |= CEPH_MOUNT_OPT_MOUNTWAIT;
		break;
	case Opt_quotadf:
		fsopt->flags &= ~CEPH_MOUNT_OPT_NOQUOTADF;
		break;
	case Opt_noquotadf:
		fsopt->flags |= CEPH_MOUNT_OPT_NOQUOTADF;
		break;
	case Opt_copyfrom:
		fsopt->flags &= ~CEPH_MOUNT_OPT_NOCOPYFROM;
		break;
	case Opt_nocopyfrom:
		fsopt->flags |= CEPH_MOUNT_OPT_NOCOPYFROM;
		break;
#ifdef CONFIG_CEPH_FS_POSIX_ACL
	case Opt_acl:
		fsopt->sb_flags |= SB_POSIXACL;
		break;
#endif
	case Opt_noacl:
		fsopt->sb_flags &= ~SB_POSIXACL;
		break;
	default:
		BUG_ON(token);
	}
	return 0;
}