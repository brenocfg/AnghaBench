#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  from; } ;
typedef  TYPE_1__ substring_t ;
struct the_nilfs {int dummy; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 int /*<<< orphan*/  DISCARD ; 
 int /*<<< orphan*/  ERRORS_CONT ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 int /*<<< orphan*/  ERRORS_RO ; 
 int /*<<< orphan*/  ERROR_MODE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  NORECOVERY ; 
#define  Opt_barrier 137 
#define  Opt_discard 136 
#define  Opt_err_cont 135 
#define  Opt_err_panic 134 
#define  Opt_err_ro 133 
#define  Opt_nobarrier 132 
#define  Opt_nodiscard 131 
#define  Opt_norecovery 130 
#define  Opt_order 129 
#define  Opt_snapshot 128 
 int /*<<< orphan*/  STRICT_ORDER ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  nilfs_clear_opt (struct the_nilfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  nilfs_set_opt (struct the_nilfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_write_opt (struct the_nilfs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int parse_options(char *options, struct super_block *sb, int is_remount)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	char *p;
	substring_t args[MAX_OPT_ARGS];

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_barrier:
			nilfs_set_opt(nilfs, BARRIER);
			break;
		case Opt_nobarrier:
			nilfs_clear_opt(nilfs, BARRIER);
			break;
		case Opt_order:
			if (strcmp(args[0].from, "relaxed") == 0)
				/* Ordered data semantics */
				nilfs_clear_opt(nilfs, STRICT_ORDER);
			else if (strcmp(args[0].from, "strict") == 0)
				/* Strict in-order semantics */
				nilfs_set_opt(nilfs, STRICT_ORDER);
			else
				return 0;
			break;
		case Opt_err_panic:
			nilfs_write_opt(nilfs, ERROR_MODE, ERRORS_PANIC);
			break;
		case Opt_err_ro:
			nilfs_write_opt(nilfs, ERROR_MODE, ERRORS_RO);
			break;
		case Opt_err_cont:
			nilfs_write_opt(nilfs, ERROR_MODE, ERRORS_CONT);
			break;
		case Opt_snapshot:
			if (is_remount) {
				nilfs_msg(sb, KERN_ERR,
					  "\"%s\" option is invalid for remount",
					  p);
				return 0;
			}
			break;
		case Opt_norecovery:
			nilfs_set_opt(nilfs, NORECOVERY);
			break;
		case Opt_discard:
			nilfs_set_opt(nilfs, DISCARD);
			break;
		case Opt_nodiscard:
			nilfs_clear_opt(nilfs, DISCARD);
			break;
		default:
			nilfs_msg(sb, KERN_ERR,
				  "unrecognized mount option \"%s\"", p);
			return 0;
		}
	}
	return 1;
}