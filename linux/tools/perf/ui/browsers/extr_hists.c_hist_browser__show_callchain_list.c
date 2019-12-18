#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct hist_browser {int /*<<< orphan*/  show_dso; } ;
struct callchain_print_arg {scalar_t__ row_offset; } ;
struct callchain_node {int dummy; } ;
struct callchain_list {int dummy; } ;
typedef  int /*<<< orphan*/  (* print_callchain_entry_fn ) (struct hist_browser*,struct callchain_list*,char const*,int,unsigned short,struct callchain_print_arg*) ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  bf ;
struct TYPE_2__ {scalar_t__ show_branchflag_count; } ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 char* callchain_list__sym_name (struct callchain_list*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_list_counts__printf_value (struct callchain_list*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  callchain_node__scnprintf_value (struct callchain_node*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int hist_browser__show_callchain_list(struct hist_browser *browser,
					     struct callchain_node *node,
					     struct callchain_list *chain,
					     unsigned short row, u64 total,
					     bool need_percent, int offset,
					     print_callchain_entry_fn print,
					     struct callchain_print_arg *arg)
{
	char bf[1024], *alloc_str;
	char buf[64], *alloc_str2;
	const char *str;
	int ret = 1;

	if (arg->row_offset != 0) {
		arg->row_offset--;
		return 0;
	}

	alloc_str = NULL;
	alloc_str2 = NULL;

	str = callchain_list__sym_name(chain, bf, sizeof(bf),
				       browser->show_dso);

	if (symbol_conf.show_branchflag_count) {
		callchain_list_counts__printf_value(chain, NULL,
						    buf, sizeof(buf));

		if (asprintf(&alloc_str2, "%s%s", str, buf) < 0)
			str = "Not enough memory!";
		else
			str = alloc_str2;
	}

	if (need_percent) {
		callchain_node__scnprintf_value(node, buf, sizeof(buf),
						total);

		if (asprintf(&alloc_str, "%s %s", buf, str) < 0)
			str = "Not enough memory!";
		else
			str = alloc_str;
	}

	print(browser, chain, str, offset, row, arg);
	free(alloc_str);
	free(alloc_str2);

	return ret;
}