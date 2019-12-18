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
struct fw_block {int /*<<< orphan*/ * name; int /*<<< orphan*/  flags; int /*<<< orphan*/  blocklen; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_HAVEHDR ; 
 int MAX_ARG_COUNT ; 
 int MAX_ARG_LEN ; 
 scalar_t__ MAX_FW_BLOCKS ; 
 int /*<<< orphan*/  dbgmsg (int,char*,char*,...) ; 
 int /*<<< orphan*/  errmsg (int /*<<< orphan*/ ,char*,...) ; 
 struct fw_block* fw_blocks ; 
 scalar_t__ fw_num_blocks ; 
 scalar_t__ is_empty_arg (char*) ; 
 int parse_arg (char*,char*,char**) ; 
 scalar_t__ required_arg (char,char*) ; 
 scalar_t__ str2u32 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

int
parse_opt_block(char ch, char *arg)
{
	char buf[MAX_ARG_LEN];
	char *argv[MAX_ARG_COUNT];
	int argc;
	struct fw_block *b;
	char *p;

	if (required_arg(ch, arg)) {
		goto err_out;
	}

	if (fw_num_blocks >= MAX_FW_BLOCKS) {
		errmsg(0,"too many blocks specified");
		goto err_out;
	}

	argc = parse_arg(arg, buf, argv);
	dbgmsg(1,"processing block option %s, count %d", arg, argc);

	b = &fw_blocks[fw_num_blocks++];

	/* processing block address */
	p = argv[0];
	if (is_empty_arg(p)) {
		errmsg(0,"no block address specified in %s", arg);
		goto err_out;
	} else if (str2u32(p, &b->addr) != 0) {
		errmsg(0,"invalid block address: %s", p);
		goto err_out;
	}

	/* processing block length */
	p = argv[1];
	if (is_empty_arg(p)) {
		errmsg(0,"no block length specified in %s", arg);
		goto err_out;
	} else if (str2u32(p, &b->blocklen) != 0) {
		errmsg(0,"invalid block length: %s", p);
		goto err_out;
	}

	if (argc < 3) {
		dbgmsg(1,"empty block %s", arg);
		goto success;
	}

	/* processing flags */
	p = argv[2];
	if (is_empty_arg(p) == 0) {
		for ( ; *p != '\0'; p++) {
			switch (*p) {
			case 'h':
				b->flags |= BLOCK_FLAG_HAVEHDR;
				break;
			default:
				errmsg(0, "invalid block flag \"%c\"", *p);
				goto err_out;
			}
		}
	}

	/* processing file name */
	p = argv[3];
	if (is_empty_arg(p)) {
		errmsg(0,"file name missing in %s", arg);
		goto err_out;
	}

	b->name = strdup(p);
	if (b->name == NULL) {
		errmsg(0,"not enough memory");
		goto err_out;
	}

success:

	return 0;

err_out:
	return -1;
}