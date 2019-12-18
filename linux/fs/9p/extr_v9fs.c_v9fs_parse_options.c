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
typedef  int uid_t ;
typedef  int /*<<< orphan*/  substring_t ;
struct v9fs_session_info {int afid; int debug; int cache; char* cachetag; long session_lock_timeout; char* uname; char* aname; int nodev; int /*<<< orphan*/  flags; void* uid; int /*<<< orphan*/  dfltgid; void* dfltuid; } ;

/* Variables and functions */
 int CACHE_FSCACHE ; 
 int CACHE_LOOSE ; 
 int CACHE_MMAP ; 
 int CACHE_NONE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 long HZ ; 
 int MAX_OPT_ARGS ; 
#define  Opt_access 142 
#define  Opt_afid 141 
#define  Opt_cache 140 
#define  Opt_cache_loose 139 
#define  Opt_cachetag 138 
#define  Opt_debug 137 
#define  Opt_dfltgid 136 
#define  Opt_dfltuid 135 
#define  Opt_fscache 134 
#define  Opt_locktimeout 133 
#define  Opt_mmap 132 
#define  Opt_nodevmap 131 
#define  Opt_posixacl 130 
#define  Opt_remotename 129 
#define  Opt_uname 128 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 long P9_LOCK_TIMEOUT ; 
 int /*<<< orphan*/  V9FS_ACCESS_ANY ; 
 int /*<<< orphan*/  V9FS_ACCESS_CLIENT ; 
 int /*<<< orphan*/  V9FS_ACCESS_MASK ; 
 int /*<<< orphan*/  V9FS_ACCESS_SINGLE ; 
 int /*<<< orphan*/  V9FS_ACCESS_USER ; 
 int /*<<< orphan*/  V9FS_POSIX_ACL ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int get_cache_mode (char*) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 void* make_kuid (int /*<<< orphan*/ ,int) ; 
 int match_int (int /*<<< orphan*/ *,int*) ; 
 void* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*) ; 
 int p9_debug_level ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int simple_strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uid_valid (void*) ; 

__attribute__((used)) static int v9fs_parse_options(struct v9fs_session_info *v9ses, char *opts)
{
	char *options, *tmp_options;
	substring_t args[MAX_OPT_ARGS];
	char *p;
	int option = 0;
	char *s, *e;
	int ret = 0;

	/* setup defaults */
	v9ses->afid = ~0;
	v9ses->debug = 0;
	v9ses->cache = CACHE_NONE;
#ifdef CONFIG_9P_FSCACHE
	v9ses->cachetag = NULL;
#endif
	v9ses->session_lock_timeout = P9_LOCK_TIMEOUT;

	if (!opts)
		return 0;

	tmp_options = kstrdup(opts, GFP_KERNEL);
	if (!tmp_options) {
		ret = -ENOMEM;
		goto fail_option_alloc;
	}
	options = tmp_options;

	while ((p = strsep(&options, ",")) != NULL) {
		int token, r;
		if (!*p)
			continue;
		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_debug:
			r = match_int(&args[0], &option);
			if (r < 0) {
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
			} else {
				v9ses->debug = option;
#ifdef CONFIG_NET_9P_DEBUG
				p9_debug_level = option;
#endif
			}
			break;

		case Opt_dfltuid:
			r = match_int(&args[0], &option);
			if (r < 0) {
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
				continue;
			}
			v9ses->dfltuid = make_kuid(current_user_ns(), option);
			if (!uid_valid(v9ses->dfltuid)) {
				p9_debug(P9_DEBUG_ERROR,
					 "uid field, but not a uid?\n");
				ret = -EINVAL;
			}
			break;
		case Opt_dfltgid:
			r = match_int(&args[0], &option);
			if (r < 0) {
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
				continue;
			}
			v9ses->dfltgid = make_kgid(current_user_ns(), option);
			if (!gid_valid(v9ses->dfltgid)) {
				p9_debug(P9_DEBUG_ERROR,
					 "gid field, but not a gid?\n");
				ret = -EINVAL;
			}
			break;
		case Opt_afid:
			r = match_int(&args[0], &option);
			if (r < 0) {
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
			} else {
				v9ses->afid = option;
			}
			break;
		case Opt_uname:
			kfree(v9ses->uname);
			v9ses->uname = match_strdup(&args[0]);
			if (!v9ses->uname) {
				ret = -ENOMEM;
				goto free_and_return;
			}
			break;
		case Opt_remotename:
			kfree(v9ses->aname);
			v9ses->aname = match_strdup(&args[0]);
			if (!v9ses->aname) {
				ret = -ENOMEM;
				goto free_and_return;
			}
			break;
		case Opt_nodevmap:
			v9ses->nodev = 1;
			break;
		case Opt_cache_loose:
			v9ses->cache = CACHE_LOOSE;
			break;
		case Opt_fscache:
			v9ses->cache = CACHE_FSCACHE;
			break;
		case Opt_mmap:
			v9ses->cache = CACHE_MMAP;
			break;
		case Opt_cachetag:
#ifdef CONFIG_9P_FSCACHE
			kfree(v9ses->cachetag);
			v9ses->cachetag = match_strdup(&args[0]);
			if (!v9ses->cachetag) {
				ret = -ENOMEM;
				goto free_and_return;
			}
#endif
			break;
		case Opt_cache:
			s = match_strdup(&args[0]);
			if (!s) {
				ret = -ENOMEM;
				p9_debug(P9_DEBUG_ERROR,
					 "problem allocating copy of cache arg\n");
				goto free_and_return;
			}
			r = get_cache_mode(s);
			if (r < 0)
				ret = r;
			else
				v9ses->cache = r;

			kfree(s);
			break;

		case Opt_access:
			s = match_strdup(&args[0]);
			if (!s) {
				ret = -ENOMEM;
				p9_debug(P9_DEBUG_ERROR,
					 "problem allocating copy of access arg\n");
				goto free_and_return;
			}

			v9ses->flags &= ~V9FS_ACCESS_MASK;
			if (strcmp(s, "user") == 0)
				v9ses->flags |= V9FS_ACCESS_USER;
			else if (strcmp(s, "any") == 0)
				v9ses->flags |= V9FS_ACCESS_ANY;
			else if (strcmp(s, "client") == 0) {
				v9ses->flags |= V9FS_ACCESS_CLIENT;
			} else {
				uid_t uid;
				v9ses->flags |= V9FS_ACCESS_SINGLE;
				uid = simple_strtoul(s, &e, 10);
				if (*e != '\0') {
					ret = -EINVAL;
					pr_info("Unknown access argument %s\n",
						s);
					kfree(s);
					continue;
				}
				v9ses->uid = make_kuid(current_user_ns(), uid);
				if (!uid_valid(v9ses->uid)) {
					ret = -EINVAL;
					pr_info("Unknown uid %s\n", s);
				}
			}

			kfree(s);
			break;

		case Opt_posixacl:
#ifdef CONFIG_9P_FS_POSIX_ACL
			v9ses->flags |= V9FS_POSIX_ACL;
#else
			p9_debug(P9_DEBUG_ERROR,
				 "Not defined CONFIG_9P_FS_POSIX_ACL. Ignoring posixacl option\n");
#endif
			break;

		case Opt_locktimeout:
			r = match_int(&args[0], &option);
			if (r < 0) {
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				ret = r;
				continue;
			}
			if (option < 1) {
				p9_debug(P9_DEBUG_ERROR,
					 "locktimeout must be a greater than zero integer.\n");
				ret = -EINVAL;
				continue;
			}
			v9ses->session_lock_timeout = (long)option * HZ;
			break;

		default:
			continue;
		}
	}

free_and_return:
	kfree(tmp_options);
fail_option_alloc:
	return ret;
}