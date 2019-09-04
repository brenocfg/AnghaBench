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
struct super_block {int dummy; } ;
struct qnx6_sb_info {int /*<<< orphan*/  s_mount_opt; } ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  MMI_FS ; 
#define  Opt_mmifs 128 
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int qnx6_parse_options(char *options, struct super_block *sb)
{
	char *p;
	struct qnx6_sb_info *sbi = QNX6_SB(sb);
	substring_t args[MAX_OPT_ARGS];

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_mmifs:
			set_opt(sbi->s_mount_opt, MMI_FS);
			break;
		default:
			return 0;
		}
	}
	return 1;
}