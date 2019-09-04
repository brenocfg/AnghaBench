#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ umode_t ;
typedef  void* uid_t ;
struct nls_table {char* charset; } ;
struct TYPE_11__ {int mft_zone_multiplier; int on_errors; int major_ver; int /*<<< orphan*/  sb; int /*<<< orphan*/  minor_ver; scalar_t__ dmask; scalar_t__ fmask; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; struct nls_table* nls_map; } ;
typedef  TYPE_1__ ntfs_volume ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  void* gid_t ;
struct TYPE_12__ {char* str; int val; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  INVALID_GID ; 
 int /*<<< orphan*/  INVALID_UID ; 
 int /*<<< orphan*/  NVolClearCaseSensitive (TYPE_1__*) ; 
 int /*<<< orphan*/  NVolClearShowSystemFiles (TYPE_1__*) ; 
 int /*<<< orphan*/  NVolClearSparseEnabled (TYPE_1__*) ; 
 int /*<<< orphan*/  NVolSetCaseSensitive (TYPE_1__*) ; 
 int /*<<< orphan*/  NVolSetShowSystemFiles (TYPE_1__*) ; 
 int /*<<< orphan*/  NVolSetSparseEnabled (TYPE_1__*) ; 
 int /*<<< orphan*/  NVolSparseEnabled (TYPE_1__*) ; 
 int ON_ERRORS_CONTINUE ; 
 int ON_ERRORS_RECOVER ; 
 int /*<<< orphan*/  current_user_ns () ; 
 scalar_t__ gid_valid (int /*<<< orphan*/ ) ; 
 struct nls_table* load_nls (char*) ; 
 struct nls_table* load_nls_default () ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ntfs_debug (char*,char*) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ntfs_warning (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* on_errors_arr ; 
 int /*<<< orphan*/  simple_getbool (char*,int*) ; 
 void* simple_strtoul (char*,char**,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_nls (struct nls_table*) ; 

__attribute__((used)) static bool parse_options(ntfs_volume *vol, char *opt)
{
	char *p, *v, *ov;
	static char *utf8 = "utf8";
	int errors = 0, sloppy = 0;
	kuid_t uid = INVALID_UID;
	kgid_t gid = INVALID_GID;
	umode_t fmask = (umode_t)-1, dmask = (umode_t)-1;
	int mft_zone_multiplier = -1, on_errors = -1;
	int show_sys_files = -1, case_sensitive = -1, disable_sparse = -1;
	struct nls_table *nls_map = NULL, *old_nls;

	/* I am lazy... (-8 */
#define NTFS_GETOPT_WITH_DEFAULT(option, variable, default_value)	\
	if (!strcmp(p, option)) {					\
		if (!v || !*v)						\
			variable = default_value;			\
		else {							\
			variable = simple_strtoul(ov = v, &v, 0);	\
			if (*v)						\
				goto needs_val;				\
		}							\
	}
#define NTFS_GETOPT(option, variable)					\
	if (!strcmp(p, option)) {					\
		if (!v || !*v)						\
			goto needs_arg;					\
		variable = simple_strtoul(ov = v, &v, 0);		\
		if (*v)							\
			goto needs_val;					\
	}
#define NTFS_GETOPT_UID(option, variable)				\
	if (!strcmp(p, option)) {					\
		uid_t uid_value;					\
		if (!v || !*v)						\
			goto needs_arg;					\
		uid_value = simple_strtoul(ov = v, &v, 0);		\
		if (*v)							\
			goto needs_val;					\
		variable = make_kuid(current_user_ns(), uid_value);	\
		if (!uid_valid(variable))				\
			goto needs_val;					\
	}
#define NTFS_GETOPT_GID(option, variable)				\
	if (!strcmp(p, option)) {					\
		gid_t gid_value;					\
		if (!v || !*v)						\
			goto needs_arg;					\
		gid_value = simple_strtoul(ov = v, &v, 0);		\
		if (*v)							\
			goto needs_val;					\
		variable = make_kgid(current_user_ns(), gid_value);	\
		if (!gid_valid(variable))				\
			goto needs_val;					\
	}
#define NTFS_GETOPT_OCTAL(option, variable)				\
	if (!strcmp(p, option)) {					\
		if (!v || !*v)						\
			goto needs_arg;					\
		variable = simple_strtoul(ov = v, &v, 8);		\
		if (*v)							\
			goto needs_val;					\
	}
#define NTFS_GETOPT_BOOL(option, variable)				\
	if (!strcmp(p, option)) {					\
		bool val;						\
		if (!simple_getbool(v, &val))				\
			goto needs_bool;				\
		variable = val;						\
	}
#define NTFS_GETOPT_OPTIONS_ARRAY(option, variable, opt_array)		\
	if (!strcmp(p, option)) {					\
		int _i;							\
		if (!v || !*v)						\
			goto needs_arg;					\
		ov = v;							\
		if (variable == -1)					\
			variable = 0;					\
		for (_i = 0; opt_array[_i].str && *opt_array[_i].str; _i++) \
			if (!strcmp(opt_array[_i].str, v)) {		\
				variable |= opt_array[_i].val;		\
				break;					\
			}						\
		if (!opt_array[_i].str || !*opt_array[_i].str)		\
			goto needs_val;					\
	}
	if (!opt || !*opt)
		goto no_mount_options;
	ntfs_debug("Entering with mount options string: %s", opt);
	while ((p = strsep(&opt, ","))) {
		if ((v = strchr(p, '=')))
			*v++ = 0;
		NTFS_GETOPT_UID("uid", uid)
		else NTFS_GETOPT_GID("gid", gid)
		else NTFS_GETOPT_OCTAL("umask", fmask = dmask)
		else NTFS_GETOPT_OCTAL("fmask", fmask)
		else NTFS_GETOPT_OCTAL("dmask", dmask)
		else NTFS_GETOPT("mft_zone_multiplier", mft_zone_multiplier)
		else NTFS_GETOPT_WITH_DEFAULT("sloppy", sloppy, true)
		else NTFS_GETOPT_BOOL("show_sys_files", show_sys_files)
		else NTFS_GETOPT_BOOL("case_sensitive", case_sensitive)
		else NTFS_GETOPT_BOOL("disable_sparse", disable_sparse)
		else NTFS_GETOPT_OPTIONS_ARRAY("errors", on_errors,
				on_errors_arr)
		else if (!strcmp(p, "posix") || !strcmp(p, "show_inodes"))
			ntfs_warning(vol->sb, "Ignoring obsolete option %s.",
					p);
		else if (!strcmp(p, "nls") || !strcmp(p, "iocharset")) {
			if (!strcmp(p, "iocharset"))
				ntfs_warning(vol->sb, "Option iocharset is "
						"deprecated. Please use "
						"option nls=<charsetname> in "
						"the future.");
			if (!v || !*v)
				goto needs_arg;
use_utf8:
			old_nls = nls_map;
			nls_map = load_nls(v);
			if (!nls_map) {
				if (!old_nls) {
					ntfs_error(vol->sb, "NLS character set "
							"%s not found.", v);
					return false;
				}
				ntfs_error(vol->sb, "NLS character set %s not "
						"found. Using previous one %s.",
						v, old_nls->charset);
				nls_map = old_nls;
			} else /* nls_map */ {
				unload_nls(old_nls);
			}
		} else if (!strcmp(p, "utf8")) {
			bool val = false;
			ntfs_warning(vol->sb, "Option utf8 is no longer "
				   "supported, using option nls=utf8. Please "
				   "use option nls=utf8 in the future and "
				   "make sure utf8 is compiled either as a "
				   "module or into the kernel.");
			if (!v || !*v)
				val = true;
			else if (!simple_getbool(v, &val))
				goto needs_bool;
			if (val) {
				v = utf8;
				goto use_utf8;
			}
		} else {
			ntfs_error(vol->sb, "Unrecognized mount option %s.", p);
			if (errors < INT_MAX)
				errors++;
		}
#undef NTFS_GETOPT_OPTIONS_ARRAY
#undef NTFS_GETOPT_BOOL
#undef NTFS_GETOPT
#undef NTFS_GETOPT_WITH_DEFAULT
	}
no_mount_options:
	if (errors && !sloppy)
		return false;
	if (sloppy)
		ntfs_warning(vol->sb, "Sloppy option given. Ignoring "
				"unrecognized mount option(s) and continuing.");
	/* Keep this first! */
	if (on_errors != -1) {
		if (!on_errors) {
			ntfs_error(vol->sb, "Invalid errors option argument "
					"or bug in options parser.");
			return false;
		}
	}
	if (nls_map) {
		if (vol->nls_map && vol->nls_map != nls_map) {
			ntfs_error(vol->sb, "Cannot change NLS character set "
					"on remount.");
			return false;
		} /* else (!vol->nls_map) */
		ntfs_debug("Using NLS character set %s.", nls_map->charset);
		vol->nls_map = nls_map;
	} else /* (!nls_map) */ {
		if (!vol->nls_map) {
			vol->nls_map = load_nls_default();
			if (!vol->nls_map) {
				ntfs_error(vol->sb, "Failed to load default "
						"NLS character set.");
				return false;
			}
			ntfs_debug("Using default NLS character set (%s).",
					vol->nls_map->charset);
		}
	}
	if (mft_zone_multiplier != -1) {
		if (vol->mft_zone_multiplier && vol->mft_zone_multiplier !=
				mft_zone_multiplier) {
			ntfs_error(vol->sb, "Cannot change mft_zone_multiplier "
					"on remount.");
			return false;
		}
		if (mft_zone_multiplier < 1 || mft_zone_multiplier > 4) {
			ntfs_error(vol->sb, "Invalid mft_zone_multiplier. "
					"Using default value, i.e. 1.");
			mft_zone_multiplier = 1;
		}
		vol->mft_zone_multiplier = mft_zone_multiplier;
	}
	if (!vol->mft_zone_multiplier)
		vol->mft_zone_multiplier = 1;
	if (on_errors != -1)
		vol->on_errors = on_errors;
	if (!vol->on_errors || vol->on_errors == ON_ERRORS_RECOVER)
		vol->on_errors |= ON_ERRORS_CONTINUE;
	if (uid_valid(uid))
		vol->uid = uid;
	if (gid_valid(gid))
		vol->gid = gid;
	if (fmask != (umode_t)-1)
		vol->fmask = fmask;
	if (dmask != (umode_t)-1)
		vol->dmask = dmask;
	if (show_sys_files != -1) {
		if (show_sys_files)
			NVolSetShowSystemFiles(vol);
		else
			NVolClearShowSystemFiles(vol);
	}
	if (case_sensitive != -1) {
		if (case_sensitive)
			NVolSetCaseSensitive(vol);
		else
			NVolClearCaseSensitive(vol);
	}
	if (disable_sparse != -1) {
		if (disable_sparse)
			NVolClearSparseEnabled(vol);
		else {
			if (!NVolSparseEnabled(vol) &&
					vol->major_ver && vol->major_ver < 3)
				ntfs_warning(vol->sb, "Not enabling sparse "
						"support due to NTFS volume "
						"version %i.%i (need at least "
						"version 3.0).", vol->major_ver,
						vol->minor_ver);
			else
				NVolSetSparseEnabled(vol);
		}
	}
	return true;
needs_arg:
	ntfs_error(vol->sb, "The %s option requires an argument.", p);
	return false;
needs_bool:
	ntfs_error(vol->sb, "The %s option requires a boolean argument.", p);
	return false;
needs_val:
	ntfs_error(vol->sb, "Invalid %s option argument: %s", p, ov);
	return false;
}