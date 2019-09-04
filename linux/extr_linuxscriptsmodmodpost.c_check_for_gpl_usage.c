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
typedef  enum export { ____Placeholder_export } export ;

/* Variables and functions */
#define  export_gpl 133 
#define  export_gpl_future 132 
#define  export_plain 131 
#define  export_unknown 130 
#define  export_unused 129 
#define  export_unused_gpl 128 
 int /*<<< orphan*/  fatal (char*,char const*,char const*,char const*) ; 
 scalar_t__ is_vmlinux (char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*,char const*,char const*) ; 

__attribute__((used)) static void check_for_gpl_usage(enum export exp, const char *m, const char *s)
{
	const char *e = is_vmlinux(m) ?"":".ko";

	switch (exp) {
	case export_gpl:
		fatal("modpost: GPL-incompatible module %s%s "
		      "uses GPL-only symbol '%s'\n", m, e, s);
		break;
	case export_unused_gpl:
		fatal("modpost: GPL-incompatible module %s%s "
		      "uses GPL-only symbol marked UNUSED '%s'\n", m, e, s);
		break;
	case export_gpl_future:
		warn("modpost: GPL-incompatible module %s%s "
		      "uses future GPL-only symbol '%s'\n", m, e, s);
		break;
	case export_plain:
	case export_unused:
	case export_unknown:
		/* ignore */
		break;
	}
}