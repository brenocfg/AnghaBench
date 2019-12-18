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
struct super_block {int /*<<< orphan*/  s_flags; } ;
struct orangefs_sb_info_s {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  ORANGEFS_OPT_INTR ; 
 int /*<<< orphan*/  ORANGEFS_OPT_LOCAL_LOCK ; 
 struct orangefs_sb_info_s* ORANGEFS_SB (struct super_block*) ; 
#define  Opt_acl 130 
#define  Opt_intr 129 
#define  Opt_local_lock 128 
 int /*<<< orphan*/  SB_POSIXACL ; 
 int /*<<< orphan*/  gossip_err (char*,char*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int parse_mount_options(struct super_block *sb, char *options,
		int silent)
{
	struct orangefs_sb_info_s *orangefs_sb = ORANGEFS_SB(sb);
	substring_t args[MAX_OPT_ARGS];
	char *p;

	/*
	 * Force any potential flags that might be set from the mount
	 * to zero, ie, initialize to unset.
	 */
	sb->s_flags &= ~SB_POSIXACL;
	orangefs_sb->flags &= ~ORANGEFS_OPT_INTR;
	orangefs_sb->flags &= ~ORANGEFS_OPT_LOCAL_LOCK;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_acl:
			sb->s_flags |= SB_POSIXACL;
			break;
		case Opt_intr:
			orangefs_sb->flags |= ORANGEFS_OPT_INTR;
			break;
		case Opt_local_lock:
			orangefs_sb->flags |= ORANGEFS_OPT_LOCAL_LOCK;
			break;
		default:
			goto fail;
		}
	}

	return 0;
fail:
	if (!silent)
		gossip_err("Error: mount option [%s] is not supported.\n", p);
	return -EINVAL;
}