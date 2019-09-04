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
struct TYPE_4__ {int /*<<< orphan*/ * from; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ substring_t ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_acl 132 
#define  Opt_fault_injection 131 
#define  Opt_noacl 130 
#define  Opt_nouser_xattr 129 
#define  Opt_user_xattr 128 
 int /*<<< orphan*/  erofs_tokens ; 
 int /*<<< orphan*/  errln (char*,char*) ; 
 int /*<<< orphan*/  infoln (char*) ; 
 int /*<<< orphan*/  match_int (TYPE_1__*,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int parse_options(struct super_block *sb, char *options)
{
	substring_t args[MAX_OPT_ARGS];
	char *p;
	int arg = 0;

	if (!options)
		return 0;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;

		if (!*p)
			continue;

		args[0].to = args[0].from = NULL;
		token = match_token(p, erofs_tokens, args);

		switch (token) {
#ifdef CONFIG_EROFS_FS_XATTR
		case Opt_user_xattr:
			set_opt(EROFS_SB(sb), XATTR_USER);
			break;
		case Opt_nouser_xattr:
			clear_opt(EROFS_SB(sb), XATTR_USER);
			break;
#else
		case Opt_user_xattr:
			infoln("user_xattr options not supported");
			break;
		case Opt_nouser_xattr:
			infoln("nouser_xattr options not supported");
			break;
#endif
#ifdef CONFIG_EROFS_FS_POSIX_ACL
		case Opt_acl:
			set_opt(EROFS_SB(sb), POSIX_ACL);
			break;
		case Opt_noacl:
			clear_opt(EROFS_SB(sb), POSIX_ACL);
			break;
#else
		case Opt_acl:
			infoln("acl options not supported");
			break;
		case Opt_noacl:
			infoln("noacl options not supported");
			break;
#endif
		case Opt_fault_injection:
			if (args->from && match_int(args, &arg))
				return -EINVAL;
#ifdef CONFIG_EROFS_FAULT_INJECTION
			erofs_build_fault_attr(EROFS_SB(sb), arg);
			set_opt(EROFS_SB(sb), FAULT_INJECTION);
#else
			infoln("FAULT_INJECTION was not selected");
#endif
			break;
		default:
			errln("Unrecognized mount option \"%s\" "
					"or missing value", p);
			return -EINVAL;
		}
	}
	return 0;
}