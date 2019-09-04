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
typedef  int /*<<< orphan*/  substring_t ;
struct gfs2_args {int ar_spectator; int ar_localflocks; int ar_debug; int ar_posix_acl; int ar_suiddir; int ar_meta; int ar_discard; int ar_commit; int ar_statfs_quantum; int ar_quota_quantum; int ar_statfs_percent; int ar_nobarrier; int ar_rgrplvb; int ar_loccookie; int /*<<< orphan*/  ar_errors; int /*<<< orphan*/  ar_data; int /*<<< orphan*/  ar_quota; int /*<<< orphan*/  ar_hostdata; int /*<<< orphan*/  ar_locktable; int /*<<< orphan*/  ar_lockproto; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFS2_DATA_ORDERED ; 
 int /*<<< orphan*/  GFS2_DATA_WRITEBACK ; 
 int /*<<< orphan*/  GFS2_ERRORS_PANIC ; 
 int /*<<< orphan*/  GFS2_ERRORS_WITHDRAW ; 
 int /*<<< orphan*/  GFS2_LOCKNAME_LEN ; 
 int /*<<< orphan*/  GFS2_QUOTA_ACCOUNT ; 
 int /*<<< orphan*/  GFS2_QUOTA_OFF ; 
 int /*<<< orphan*/  GFS2_QUOTA_ON ; 
 int MAX_OPT_ARGS ; 
#define  Opt_acl 164 
#define  Opt_barrier 163 
#define  Opt_commit 162 
#define  Opt_data_ordered 161 
#define  Opt_data_writeback 160 
#define  Opt_debug 159 
#define  Opt_discard 158 
#define  Opt_err_panic 157 
#define  Opt_err_withdraw 156 
#define  Opt_error 155 
#define  Opt_hostdata 154 
#define  Opt_ignore_local_fs 153 
#define  Opt_localcaching 152 
#define  Opt_localflocks 151 
#define  Opt_loccookie 150 
#define  Opt_lockproto 149 
#define  Opt_locktable 148 
#define  Opt_meta 147 
#define  Opt_noacl 146 
#define  Opt_nobarrier 145 
#define  Opt_nodebug 144 
#define  Opt_nodiscard 143 
#define  Opt_noloccookie 142 
#define  Opt_noquota 141 
#define  Opt_norgrplvb 140 
#define  Opt_nosuiddir 139 
#define  Opt_quota 138 
#define  Opt_quota_account 137 
#define  Opt_quota_off 136 
#define  Opt_quota_on 135 
#define  Opt_quota_quantum 134 
#define  Opt_rgrplvb 133 
#define  Opt_spectator 132 
#define  Opt_statfs_percent 131 
#define  Opt_statfs_quantum 130 
#define  Opt_suiddir 129 
#define  Opt_upgrade 128 
 int match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

int gfs2_mount_args(struct gfs2_args *args, char *options)
{
	char *o;
	int token;
	substring_t tmp[MAX_OPT_ARGS];
	int rv;

	/* Split the options into tokens with the "," character and
	   process them */

	while (1) {
		o = strsep(&options, ",");
		if (o == NULL)
			break;
		if (*o == '\0')
			continue;

		token = match_token(o, tokens, tmp);
		switch (token) {
		case Opt_lockproto:
			match_strlcpy(args->ar_lockproto, &tmp[0],
				      GFS2_LOCKNAME_LEN);
			break;
		case Opt_locktable:
			match_strlcpy(args->ar_locktable, &tmp[0],
				      GFS2_LOCKNAME_LEN);
			break;
		case Opt_hostdata:
			match_strlcpy(args->ar_hostdata, &tmp[0],
				      GFS2_LOCKNAME_LEN);
			break;
		case Opt_spectator:
			args->ar_spectator = 1;
			break;
		case Opt_ignore_local_fs:
			/* Retained for backwards compat only */
			break;
		case Opt_localflocks:
			args->ar_localflocks = 1;
			break;
		case Opt_localcaching:
			/* Retained for backwards compat only */
			break;
		case Opt_debug:
			if (args->ar_errors == GFS2_ERRORS_PANIC) {
				pr_warn("-o debug and -o errors=panic are mutually exclusive\n");
				return -EINVAL;
			}
			args->ar_debug = 1;
			break;
		case Opt_nodebug:
			args->ar_debug = 0;
			break;
		case Opt_upgrade:
			/* Retained for backwards compat only */
			break;
		case Opt_acl:
			args->ar_posix_acl = 1;
			break;
		case Opt_noacl:
			args->ar_posix_acl = 0;
			break;
		case Opt_quota_off:
		case Opt_noquota:
			args->ar_quota = GFS2_QUOTA_OFF;
			break;
		case Opt_quota_account:
			args->ar_quota = GFS2_QUOTA_ACCOUNT;
			break;
		case Opt_quota_on:
		case Opt_quota:
			args->ar_quota = GFS2_QUOTA_ON;
			break;
		case Opt_suiddir:
			args->ar_suiddir = 1;
			break;
		case Opt_nosuiddir:
			args->ar_suiddir = 0;
			break;
		case Opt_data_writeback:
			args->ar_data = GFS2_DATA_WRITEBACK;
			break;
		case Opt_data_ordered:
			args->ar_data = GFS2_DATA_ORDERED;
			break;
		case Opt_meta:
			args->ar_meta = 1;
			break;
		case Opt_discard:
			args->ar_discard = 1;
			break;
		case Opt_nodiscard:
			args->ar_discard = 0;
			break;
		case Opt_commit:
			rv = match_int(&tmp[0], &args->ar_commit);
			if (rv || args->ar_commit <= 0) {
				pr_warn("commit mount option requires a positive numeric argument\n");
				return rv ? rv : -EINVAL;
			}
			break;
		case Opt_statfs_quantum:
			rv = match_int(&tmp[0], &args->ar_statfs_quantum);
			if (rv || args->ar_statfs_quantum < 0) {
				pr_warn("statfs_quantum mount option requires a non-negative numeric argument\n");
				return rv ? rv : -EINVAL;
			}
			break;
		case Opt_quota_quantum:
			rv = match_int(&tmp[0], &args->ar_quota_quantum);
			if (rv || args->ar_quota_quantum <= 0) {
				pr_warn("quota_quantum mount option requires a positive numeric argument\n");
				return rv ? rv : -EINVAL;
			}
			break;
		case Opt_statfs_percent:
			rv = match_int(&tmp[0], &args->ar_statfs_percent);
			if (rv || args->ar_statfs_percent < 0 ||
			    args->ar_statfs_percent > 100) {
				pr_warn("statfs_percent mount option requires a numeric argument between 0 and 100\n");
				return rv ? rv : -EINVAL;
			}
			break;
		case Opt_err_withdraw:
			args->ar_errors = GFS2_ERRORS_WITHDRAW;
			break;
		case Opt_err_panic:
			if (args->ar_debug) {
				pr_warn("-o debug and -o errors=panic are mutually exclusive\n");
				return -EINVAL;
			}
			args->ar_errors = GFS2_ERRORS_PANIC;
			break;
		case Opt_barrier:
			args->ar_nobarrier = 0;
			break;
		case Opt_nobarrier:
			args->ar_nobarrier = 1;
			break;
		case Opt_rgrplvb:
			args->ar_rgrplvb = 1;
			break;
		case Opt_norgrplvb:
			args->ar_rgrplvb = 0;
			break;
		case Opt_loccookie:
			args->ar_loccookie = 1;
			break;
		case Opt_noloccookie:
			args->ar_loccookie = 0;
			break;
		case Opt_error:
		default:
			pr_warn("invalid mount option: %s\n", o);
			return -EINVAL;
		}
	}

	return 0;
}