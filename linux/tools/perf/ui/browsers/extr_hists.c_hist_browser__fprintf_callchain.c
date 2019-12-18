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
struct hist_entry {int dummy; } ;
struct hist_browser {int dummy; } ;
struct callchain_print_arg {int printed; int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  hist_browser__check_dump_full ; 
 int /*<<< orphan*/  hist_browser__fprintf_callchain_entry ; 
 int /*<<< orphan*/  hist_browser__show_callchain (struct hist_browser*,struct hist_entry*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct callchain_print_arg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_browser__fprintf_callchain(struct hist_browser *browser,
					   struct hist_entry *he, FILE *fp,
					   int level)
{
	struct callchain_print_arg arg  = {
		.fp = fp,
	};

	hist_browser__show_callchain(browser, he, level, 0,
				     hist_browser__fprintf_callchain_entry, &arg,
				     hist_browser__check_dump_full);
	return arg.printed;
}