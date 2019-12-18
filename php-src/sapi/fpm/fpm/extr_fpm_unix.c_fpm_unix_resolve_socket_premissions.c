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
struct passwd {int pw_uid; int pw_gid; } ;
struct group {int gr_gid; } ;
struct fpm_worker_pool_s {int socket_uid; int socket_gid; int socket_mode; struct fpm_worker_pool_config_s* config; int /*<<< orphan*/ * socket_acl; } ;
struct fpm_worker_pool_config_s {char* listen_acl_users; char* listen_acl_groups; char* listen_owner; char* listen_group; int /*<<< orphan*/  name; scalar_t__* listen_mode; } ;
typedef  int /*<<< orphan*/ * acl_t ;
typedef  int /*<<< orphan*/  acl_permset_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_GROUP ; 
 int /*<<< orphan*/  ACL_READ ; 
 int /*<<< orphan*/  ACL_USER ; 
 int /*<<< orphan*/  ACL_WRITE ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 scalar_t__ acl_add_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acl_clear_perms (int /*<<< orphan*/ ) ; 
 scalar_t__ acl_create_entry (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ *) ; 
 scalar_t__ acl_get_permset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acl_init (int) ; 
 scalar_t__ acl_set_qualifier (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ acl_set_tag_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char*) ; 
 struct group* getgrnam (char*) ; 
 struct passwd* getpwnam (char*) ; 
 char* strchr (char*,char) ; 
 int strtoul (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

int fpm_unix_resolve_socket_premissions(struct fpm_worker_pool_s *wp) /* {{{ */
{
	struct fpm_worker_pool_config_s *c = wp->config;
#ifdef HAVE_FPM_ACL
	int n;

	/* uninitialized */
	wp->socket_acl  = NULL;
#endif
	wp->socket_uid = -1;
	wp->socket_gid = -1;
	wp->socket_mode = 0660;

	if (!c) {
		return 0;
	}

	if (c->listen_mode && *c->listen_mode) {
		wp->socket_mode = strtoul(c->listen_mode, 0, 8);
	}

#ifdef HAVE_FPM_ACL
	/* count the users and groups configured */
	n = 0;
	if (c->listen_acl_users && *c->listen_acl_users) {
		char *p;
		n++;
		for (p=strchr(c->listen_acl_users, ',') ; p ; p=strchr(p+1, ',')) {
			n++;
		}
	}
	if (c->listen_acl_groups && *c->listen_acl_groups) {
		char *p;
		n++;
		for (p=strchr(c->listen_acl_groups, ',') ; p ; p=strchr(p+1, ',')) {
			n++;
		}
	}
	/* if ACL configured */
	if (n) {
		acl_t acl;
		acl_entry_t entry;
		acl_permset_t perm;
		char *tmp, *p, *end;

		acl = acl_init(n);
		if (!acl) {
			zlog(ZLOG_SYSERROR, "[pool %s] cannot allocate ACL", wp->config->name);
			return -1;
		}
		/* Create USER ACL */
		if (c->listen_acl_users && *c->listen_acl_users) {
			struct passwd *pwd;

			tmp = estrdup(c->listen_acl_users);
			for (p=tmp ; p ; p=end) {
				if ((end = strchr(p, ','))) {
					*end++ = 0;
				}
				pwd = getpwnam(p);
				if (pwd) {
					zlog(ZLOG_DEBUG, "[pool %s] user '%s' have uid=%d", wp->config->name, p, pwd->pw_uid);
				} else {
					zlog(ZLOG_SYSERROR, "[pool %s] cannot get uid for user '%s'", wp->config->name, p);
					acl_free(acl);
					efree(tmp);
					return -1;
				}
				if (0 > acl_create_entry(&acl, &entry) ||
					0 > acl_set_tag_type(entry, ACL_USER) ||
					0 > acl_set_qualifier(entry, &pwd->pw_uid) ||
					0 > acl_get_permset(entry, &perm) ||
					0 > acl_clear_perms (perm) ||
					0 > acl_add_perm (perm, ACL_READ) ||
					0 > acl_add_perm (perm, ACL_WRITE)) {
					zlog(ZLOG_SYSERROR, "[pool %s] cannot create ACL for user '%s'", wp->config->name, p);
					acl_free(acl);
					efree(tmp);
					return -1;
				}
			}
			efree(tmp);
		}
		/* Create GROUP ACL */
		if (c->listen_acl_groups && *c->listen_acl_groups) {
			struct group *grp;

			tmp = estrdup(c->listen_acl_groups);
			for (p=tmp ; p ; p=end) {
				if ((end = strchr(p, ','))) {
					*end++ = 0;
				}
				grp = getgrnam(p);
				if (grp) {
					zlog(ZLOG_DEBUG, "[pool %s] group '%s' have gid=%d", wp->config->name, p, grp->gr_gid);
				} else {
					zlog(ZLOG_SYSERROR, "[pool %s] cannot get gid for group '%s'", wp->config->name, p);
					acl_free(acl);
					efree(tmp);
					return -1;
				}
				if (0 > acl_create_entry(&acl, &entry) ||
					0 > acl_set_tag_type(entry, ACL_GROUP) ||
					0 > acl_set_qualifier(entry, &grp->gr_gid) ||
					0 > acl_get_permset(entry, &perm) ||
					0 > acl_clear_perms (perm) ||
					0 > acl_add_perm (perm, ACL_READ) ||
					0 > acl_add_perm (perm, ACL_WRITE)) {
					zlog(ZLOG_SYSERROR, "[pool %s] cannot create ACL for group '%s'", wp->config->name, p);
					acl_free(acl);
					efree(tmp);
					return -1;
				}
			}
			efree(tmp);
		}
		if (c->listen_owner && *c->listen_owner) {
			zlog(ZLOG_WARNING, "[pool %s] ACL set, listen.owner = '%s' is ignored", wp->config->name, c->listen_owner);
		}
		if (c->listen_group && *c->listen_group) {
			zlog(ZLOG_WARNING, "[pool %s] ACL set, listen.group = '%s' is ignored", wp->config->name, c->listen_group);
		}
		wp->socket_acl  = acl;
		return 0;
	}
	/* When listen.users and listen.groups not configured, continue with standard right */
#endif

	if (c->listen_owner && *c->listen_owner) {
		struct passwd *pwd;

		pwd = getpwnam(c->listen_owner);
		if (!pwd) {
			zlog(ZLOG_SYSERROR, "[pool %s] cannot get uid for user '%s'", wp->config->name, c->listen_owner);
			return -1;
		}

		wp->socket_uid = pwd->pw_uid;
		wp->socket_gid = pwd->pw_gid;
	}

	if (c->listen_group && *c->listen_group) {
		struct group *grp;

		grp = getgrnam(c->listen_group);
		if (!grp) {
			zlog(ZLOG_SYSERROR, "[pool %s] cannot get gid for group '%s'", wp->config->name, c->listen_group);
			return -1;
		}
		wp->socket_gid = grp->gr_gid;
	}

	return 0;
}