#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uid_t ;
struct TYPE_4__ {char* from; } ;
typedef  TYPE_1__ substring_t ;
struct super_block {scalar_t__ s_blocksize_bits; TYPE_3__* s_bdev; } ;
struct request_queue {int dummy; } ;
struct jfs_sb_info {int umask; int minblks_trim; void* nls_tab; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  scalar_t__ s64 ;
typedef  int gid_t ;
struct TYPE_5__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int JFS_DISCARD ; 
 int JFS_ERR_CONTINUE ; 
 int JFS_ERR_PANIC ; 
 int JFS_ERR_REMOUNT_RO ; 
 int JFS_GRPQUOTA ; 
 int JFS_NOINTEGRITY ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int JFS_USRQUOTA ; 
 int MAX_OPT_ARGS ; 
#define  Opt_discard 143 
#define  Opt_discard_minblk 142 
#define  Opt_errors 141 
#define  Opt_gid 140 
#define  Opt_grpquota 139 
#define  Opt_ignore 138 
#define  Opt_integrity 137 
#define  Opt_iocharset 136 
#define  Opt_nodiscard 135 
#define  Opt_nointegrity 134 
#define  Opt_quota 133 
#define  Opt_resize 132 
#define  Opt_resize_nosize 131 
#define  Opt_uid 130 
#define  Opt_umask 129 
#define  Opt_usrquota 128 
 struct request_queue* bdev_get_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  blk_queue_discard (struct request_queue*) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 int kstrtoll (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int kstrtouint (char*,int,int*) ; 
 void* load_nls (char*) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_nls (void*) ; 

__attribute__((used)) static int parse_options(char *options, struct super_block *sb, s64 *newLVSize,
			 int *flag)
{
	void *nls_map = (void *)-1;	/* -1: no change;  NULL: none */
	char *p;
	struct jfs_sb_info *sbi = JFS_SBI(sb);

	*newLVSize = 0;

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		substring_t args[MAX_OPT_ARGS];
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_integrity:
			*flag &= ~JFS_NOINTEGRITY;
			break;
		case Opt_nointegrity:
			*flag |= JFS_NOINTEGRITY;
			break;
		case Opt_ignore:
			/* Silently ignore the quota options */
			/* Don't do anything ;-) */
			break;
		case Opt_iocharset:
			if (nls_map && nls_map != (void *) -1)
				unload_nls(nls_map);
			if (!strcmp(args[0].from, "none"))
				nls_map = NULL;
			else {
				nls_map = load_nls(args[0].from);
				if (!nls_map) {
					pr_err("JFS: charset not found\n");
					goto cleanup;
				}
			}
			break;
		case Opt_resize:
		{
			char *resize = args[0].from;
			int rc = kstrtoll(resize, 0, newLVSize);

			if (rc)
				goto cleanup;
			break;
		}
		case Opt_resize_nosize:
		{
			*newLVSize = i_size_read(sb->s_bdev->bd_inode) >>
				sb->s_blocksize_bits;
			if (*newLVSize == 0)
				pr_err("JFS: Cannot determine volume size\n");
			break;
		}
		case Opt_errors:
		{
			char *errors = args[0].from;
			if (!errors || !*errors)
				goto cleanup;
			if (!strcmp(errors, "continue")) {
				*flag &= ~JFS_ERR_REMOUNT_RO;
				*flag &= ~JFS_ERR_PANIC;
				*flag |= JFS_ERR_CONTINUE;
			} else if (!strcmp(errors, "remount-ro")) {
				*flag &= ~JFS_ERR_CONTINUE;
				*flag &= ~JFS_ERR_PANIC;
				*flag |= JFS_ERR_REMOUNT_RO;
			} else if (!strcmp(errors, "panic")) {
				*flag &= ~JFS_ERR_CONTINUE;
				*flag &= ~JFS_ERR_REMOUNT_RO;
				*flag |= JFS_ERR_PANIC;
			} else {
				pr_err("JFS: %s is an invalid error handler\n",
				       errors);
				goto cleanup;
			}
			break;
		}

#ifdef CONFIG_QUOTA
		case Opt_quota:
		case Opt_usrquota:
			*flag |= JFS_USRQUOTA;
			break;
		case Opt_grpquota:
			*flag |= JFS_GRPQUOTA;
			break;
#else
		case Opt_usrquota:
		case Opt_grpquota:
		case Opt_quota:
			pr_err("JFS: quota operations not supported\n");
			break;
#endif
		case Opt_uid:
		{
			char *uid = args[0].from;
			uid_t val;
			int rc = kstrtouint(uid, 0, &val);

			if (rc)
				goto cleanup;
			sbi->uid = make_kuid(current_user_ns(), val);
			if (!uid_valid(sbi->uid))
				goto cleanup;
			break;
		}

		case Opt_gid:
		{
			char *gid = args[0].from;
			gid_t val;
			int rc = kstrtouint(gid, 0, &val);

			if (rc)
				goto cleanup;
			sbi->gid = make_kgid(current_user_ns(), val);
			if (!gid_valid(sbi->gid))
				goto cleanup;
			break;
		}

		case Opt_umask:
		{
			char *umask = args[0].from;
			int rc = kstrtouint(umask, 8, &sbi->umask);

			if (rc)
				goto cleanup;
			if (sbi->umask & ~0777) {
				pr_err("JFS: Invalid value of umask\n");
				goto cleanup;
			}
			break;
		}

		case Opt_discard:
		{
			struct request_queue *q = bdev_get_queue(sb->s_bdev);
			/* if set to 1, even copying files will cause
			 * trimming :O
			 * -> user has more control over the online trimming
			 */
			sbi->minblks_trim = 64;
			if (blk_queue_discard(q))
				*flag |= JFS_DISCARD;
			else
				pr_err("JFS: discard option not supported on device\n");
			break;
		}

		case Opt_nodiscard:
			*flag &= ~JFS_DISCARD;
			break;

		case Opt_discard_minblk:
		{
			struct request_queue *q = bdev_get_queue(sb->s_bdev);
			char *minblks_trim = args[0].from;
			int rc;
			if (blk_queue_discard(q)) {
				*flag |= JFS_DISCARD;
				rc = kstrtouint(minblks_trim, 0,
						&sbi->minblks_trim);
				if (rc)
					goto cleanup;
			} else
				pr_err("JFS: discard option not supported on device\n");
			break;
		}

		default:
			printk("jfs: Unrecognized mount option \"%s\" or missing value\n",
			       p);
			goto cleanup;
		}
	}

	if (nls_map != (void *) -1) {
		/* Discard old (if remount) */
		unload_nls(sbi->nls_tab);
		sbi->nls_tab = nls_map;
	}
	return 1;

cleanup:
	if (nls_map && nls_map != (void *) -1)
		unload_nls(nls_map);
	return 0;
}