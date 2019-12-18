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
struct TYPE_3__ {char const opt_char; unsigned int flag; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* opt_array ; 
 int /*<<< orphan*/  pr_err (char*,char const,char const*) ; 
 int /*<<< orphan*/  vpr_info (char*,unsigned int,...) ; 

__attribute__((used)) static int ddebug_parse_flags(const char *str, unsigned int *flagsp,
			       unsigned int *maskp)
{
	unsigned flags = 0;
	int op = '=', i;

	switch (*str) {
	case '+':
	case '-':
	case '=':
		op = *str++;
		break;
	default:
		pr_err("bad flag-op %c, at start of %s\n", *str, str);
		return -EINVAL;
	}
	vpr_info("op='%c'\n", op);

	for (; *str ; ++str) {
		for (i = ARRAY_SIZE(opt_array) - 1; i >= 0; i--) {
			if (*str == opt_array[i].opt_char) {
				flags |= opt_array[i].flag;
				break;
			}
		}
		if (i < 0) {
			pr_err("unknown flag '%c' in \"%s\"\n", *str, str);
			return -EINVAL;
		}
	}
	vpr_info("flags=0x%x\n", flags);

	/* calculate final *flagsp, *maskp according to mask and op */
	switch (op) {
	case '=':
		*maskp = 0;
		*flagsp = flags;
		break;
	case '+':
		*maskp = ~0U;
		*flagsp = flags;
		break;
	case '-':
		*maskp = ~flags;
		*flagsp = 0;
		break;
	}
	vpr_info("*flagsp=0x%x *maskp=0x%x\n", *flagsp, *maskp);
	return 0;
}