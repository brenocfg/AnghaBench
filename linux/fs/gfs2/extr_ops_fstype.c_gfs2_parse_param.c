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
struct gfs2_args {int ar_spectator; int ar_localflocks; int ar_meta; size_t ar_commit; size_t ar_statfs_quantum; size_t ar_quota_quantum; int ar_statfs_percent; int /*<<< orphan*/  ar_loccookie; int /*<<< orphan*/  ar_rgrplvb; int /*<<< orphan*/  ar_nobarrier; int /*<<< orphan*/  ar_errors; int /*<<< orphan*/  ar_debug; int /*<<< orphan*/  ar_discard; int /*<<< orphan*/  ar_data; int /*<<< orphan*/  ar_suiddir; int /*<<< orphan*/  ar_quota; int /*<<< orphan*/  ar_posix_acl; int /*<<< orphan*/  ar_hostdata; int /*<<< orphan*/  ar_locktable; int /*<<< orphan*/  ar_lockproto; } ;
struct fs_parse_result {size_t int_32; int /*<<< orphan*/  boolean; int /*<<< orphan*/  uint_32; int /*<<< orphan*/  negated; } ;
struct fs_parameter {int /*<<< orphan*/  key; int /*<<< orphan*/  string; } ;
struct fs_context {struct gfs2_args* fs_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_ERRORS_PANIC ; 
 int /*<<< orphan*/  GFS2_LOCKNAME_LEN ; 
 int /*<<< orphan*/  GFS2_QUOTA_OFF ; 
 int /*<<< orphan*/  GFS2_QUOTA_ON ; 
#define  Opt_acl 150 
#define  Opt_barrier 149 
#define  Opt_commit 148 
#define  Opt_data 147 
#define  Opt_debug 146 
#define  Opt_discard 145 
#define  Opt_errors 144 
#define  Opt_hostdata 143 
#define  Opt_ignore_local_fs 142 
#define  Opt_localcaching 141 
#define  Opt_localflocks 140 
#define  Opt_loccookie 139 
#define  Opt_lockproto 138 
#define  Opt_locktable 137 
#define  Opt_meta 136 
#define  Opt_quota 135 
#define  Opt_quota_quantum 134 
#define  Opt_rgrplvb 133 
#define  Opt_spectator 132 
#define  Opt_statfs_percent 131 
#define  Opt_statfs_quantum 130 
#define  Opt_suiddir 129 
#define  Opt_upgrade 128 
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 
 int /*<<< orphan*/  gfs2_fs_parameters ; 
 int invalf (struct fs_context*,char*,...) ; 
 int /*<<< orphan*/ * opt_quota_values ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	struct gfs2_args *args = fc->fs_private;
	struct fs_parse_result result;
	int o;

	o = fs_parse(fc, &gfs2_fs_parameters, param, &result);
	if (o < 0)
		return o;

	switch (o) {
	case Opt_lockproto:
		strlcpy(args->ar_lockproto, param->string, GFS2_LOCKNAME_LEN);
		break;
	case Opt_locktable:
		strlcpy(args->ar_locktable, param->string, GFS2_LOCKNAME_LEN);
		break;
	case Opt_hostdata:
		strlcpy(args->ar_hostdata, param->string, GFS2_LOCKNAME_LEN);
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
		if (result.boolean && args->ar_errors == GFS2_ERRORS_PANIC)
			return invalf(fc, "gfs2: -o debug and -o errors=panic are mutually exclusive");
		args->ar_debug = result.boolean;
		break;
	case Opt_upgrade:
		/* Retained for backwards compat only */
		break;
	case Opt_acl:
		args->ar_posix_acl = result.boolean;
		break;
	case Opt_quota:
		/* The quota option can be a flag or an enum. A non-zero int_32
		   result means that we have an enum index. Otherwise we have
		   to rely on the 'negated' flag to tell us whether 'quota' or
		   'noquota' was specified. */
		if (result.negated)
			args->ar_quota = GFS2_QUOTA_OFF;
		else if (result.int_32 > 0)
			args->ar_quota = opt_quota_values[result.int_32];
		else
			args->ar_quota = GFS2_QUOTA_ON;
		break;
	case Opt_suiddir:
		args->ar_suiddir = result.boolean;
		break;
	case Opt_data:
		/* The uint_32 result maps directly to GFS2_DATA_* */
		args->ar_data = result.uint_32;
		break;
	case Opt_meta:
		args->ar_meta = 1;
		break;
	case Opt_discard:
		args->ar_discard = result.boolean;
		break;
	case Opt_commit:
		if (result.int_32 <= 0)
			return invalf(fc, "gfs2: commit mount option requires a positive numeric argument");
		args->ar_commit = result.int_32;
		break;
	case Opt_statfs_quantum:
		if (result.int_32 < 0)
			return invalf(fc, "gfs2: statfs_quantum mount option requires a non-negative numeric argument");
		args->ar_statfs_quantum = result.int_32;
		break;
	case Opt_quota_quantum:
		if (result.int_32 <= 0)
			return invalf(fc, "gfs2: quota_quantum mount option requires a positive numeric argument");
		args->ar_quota_quantum = result.int_32;
		break;
	case Opt_statfs_percent:
		if (result.int_32 < 0 || result.int_32 > 100)
			return invalf(fc, "gfs2: statfs_percent mount option requires a numeric argument between 0 and 100");
		args->ar_statfs_percent = result.int_32;
		break;
	case Opt_errors:
		if (args->ar_debug && result.uint_32 == GFS2_ERRORS_PANIC)
			return invalf(fc, "gfs2: -o debug and -o errors=panic are mutually exclusive");
		args->ar_errors = result.uint_32;
		break;
	case Opt_barrier:
		args->ar_nobarrier = result.boolean;
		break;
	case Opt_rgrplvb:
		args->ar_rgrplvb = result.boolean;
		break;
	case Opt_loccookie:
		args->ar_loccookie = result.boolean;
		break;
	default:
		return invalf(fc, "gfs2: invalid mount option: %s", param->key);
	}
	return 0;
}