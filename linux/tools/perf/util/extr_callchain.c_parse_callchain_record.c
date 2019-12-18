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
struct callchain_param {unsigned long dump_size; int /*<<< orphan*/  record_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLCHAIN_DWARF ; 
 int /*<<< orphan*/  CALLCHAIN_FP ; 
 int /*<<< orphan*/  CALLCHAIN_LBR ; 
 int ENOMEM ; 
 int dwarf_callchain_users ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_stack_size (char*,unsigned long*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strtok_r (char*,char*,char**) ; 

int parse_callchain_record(const char *arg, struct callchain_param *param)
{
	char *tok, *name, *saveptr = NULL;
	char *buf;
	int ret = -1;

	/* We need buffer that we know we can write to. */
	buf = malloc(strlen(arg) + 1);
	if (!buf)
		return -ENOMEM;

	strcpy(buf, arg);

	tok = strtok_r((char *)buf, ",", &saveptr);
	name = tok ? : (char *)buf;

	do {
		/* Framepointer style */
		if (!strncmp(name, "fp", sizeof("fp"))) {
			if (!strtok_r(NULL, ",", &saveptr)) {
				param->record_mode = CALLCHAIN_FP;
				ret = 0;
			} else
				pr_err("callchain: No more arguments "
				       "needed for --call-graph fp\n");
			break;

		/* Dwarf style */
		} else if (!strncmp(name, "dwarf", sizeof("dwarf"))) {
			const unsigned long default_stack_dump_size = 8192;

			ret = 0;
			param->record_mode = CALLCHAIN_DWARF;
			param->dump_size = default_stack_dump_size;
			dwarf_callchain_users = true;

			tok = strtok_r(NULL, ",", &saveptr);
			if (tok) {
				unsigned long size = 0;

				ret = get_stack_size(tok, &size);
				param->dump_size = size;
			}
		} else if (!strncmp(name, "lbr", sizeof("lbr"))) {
			if (!strtok_r(NULL, ",", &saveptr)) {
				param->record_mode = CALLCHAIN_LBR;
				ret = 0;
			} else
				pr_err("callchain: No more arguments "
					"needed for --call-graph lbr\n");
			break;
		} else {
			pr_err("callchain: Unknown --call-graph option "
			       "value: %s\n", arg);
			break;
		}

	} while (0);

	free(buf);
	return ret;
}