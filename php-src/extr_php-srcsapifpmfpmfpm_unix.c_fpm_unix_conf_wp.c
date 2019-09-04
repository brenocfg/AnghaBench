#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct passwd {scalar_t__ pw_uid; scalar_t__ pw_gid; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_name; } ;
struct group {scalar_t__ gr_gid; } ;
struct fpm_worker_pool_s {scalar_t__ set_uid; scalar_t__ set_gid; void* home; void* user; TYPE_1__* config; } ;
struct TYPE_4__ {int /*<<< orphan*/  run_as_root; } ;
struct TYPE_3__ {int process_priority; int /*<<< orphan*/  name; scalar_t__* chroot; scalar_t__* group; scalar_t__* user; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 TYPE_2__ fpm_globals ; 
 int /*<<< orphan*/  geteuid () ; 
 struct group* getgrnam (scalar_t__*) ; 
 struct passwd* getpwnam (scalar_t__*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (scalar_t__*) ; 
 scalar_t__ strspn (scalar_t__*,char*) ; 
 void* strtoul (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int fpm_unix_conf_wp(struct fpm_worker_pool_s *wp) /* {{{ */
{
	struct passwd *pwd;
	int is_root = !geteuid();

	if (is_root) {
		if (wp->config->user && *wp->config->user) {
			if (strlen(wp->config->user) == strspn(wp->config->user, "0123456789")) {
				wp->set_uid = strtoul(wp->config->user, 0, 10);
			} else {
				struct passwd *pwd;

				pwd = getpwnam(wp->config->user);
				if (!pwd) {
					zlog(ZLOG_ERROR, "[pool %s] cannot get uid for user '%s'", wp->config->name, wp->config->user);
					return -1;
				}

				wp->set_uid = pwd->pw_uid;
				wp->set_gid = pwd->pw_gid;

				wp->user = strdup(pwd->pw_name);
				wp->home = strdup(pwd->pw_dir);
			}
		}

		if (wp->config->group && *wp->config->group) {
			if (strlen(wp->config->group) == strspn(wp->config->group, "0123456789")) {
				wp->set_gid = strtoul(wp->config->group, 0, 10);
			} else {
				struct group *grp;

				grp = getgrnam(wp->config->group);
				if (!grp) {
					zlog(ZLOG_ERROR, "[pool %s] cannot get gid for group '%s'", wp->config->name, wp->config->group);
					return -1;
				}
				wp->set_gid = grp->gr_gid;
			}
		}

		if (!fpm_globals.run_as_root) {
			if (wp->set_uid == 0 || wp->set_gid == 0) {
				zlog(ZLOG_ERROR, "[pool %s] please specify user and group other than root", wp->config->name);
				return -1;
			}
		}
	} else { /* not root */
		if (wp->config->user && *wp->config->user) {
			zlog(ZLOG_NOTICE, "[pool %s] 'user' directive is ignored when FPM is not running as root", wp->config->name);
		}
		if (wp->config->group && *wp->config->group) {
			zlog(ZLOG_NOTICE, "[pool %s] 'group' directive is ignored when FPM is not running as root", wp->config->name);
		}
		if (wp->config->chroot && *wp->config->chroot) {
			zlog(ZLOG_NOTICE, "[pool %s] 'chroot' directive is ignored when FPM is not running as root", wp->config->name);
		}
		if (wp->config->process_priority != 64) {
			zlog(ZLOG_NOTICE, "[pool %s] 'process.priority' directive is ignored when FPM is not running as root", wp->config->name);
		}

		/* set up HOME and USER anyway */
		pwd = getpwuid(getuid());
		if (pwd) {
			wp->user = strdup(pwd->pw_name);
			wp->home = strdup(pwd->pw_dir);
		}
	}
	return 0;
}