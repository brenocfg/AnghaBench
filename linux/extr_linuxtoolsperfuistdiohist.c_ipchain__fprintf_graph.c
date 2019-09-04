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
struct callchain_node {int dummy; } ;
struct callchain_list {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  bf ;
struct TYPE_2__ {scalar_t__ show_branchflag_count; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,char*) ; 
 scalar_t__ callchain__fprintf_left_margin (int /*<<< orphan*/ *,int) ; 
 char* callchain_list__sym_name (struct callchain_list*,char*,int,int) ; 
 int /*<<< orphan*/  callchain_list_counts__printf_value (struct callchain_list*,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ callchain_node__fprintf_value (struct callchain_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static size_t ipchain__fprintf_graph(FILE *fp, struct callchain_node *node,
				     struct callchain_list *chain,
				     int depth, int depth_mask, int period,
				     u64 total_samples, int left_margin)
{
	int i;
	size_t ret = 0;
	char bf[1024], *alloc_str = NULL;
	char buf[64];
	const char *str;

	ret += callchain__fprintf_left_margin(fp, left_margin);
	for (i = 0; i < depth; i++) {
		if (depth_mask & (1 << i))
			ret += fprintf(fp, "|");
		else
			ret += fprintf(fp, " ");
		if (!period && i == depth - 1) {
			ret += fprintf(fp, "--");
			ret += callchain_node__fprintf_value(node, fp, total_samples);
			ret += fprintf(fp, "--");
		} else
			ret += fprintf(fp, "%s", "          ");
	}

	str = callchain_list__sym_name(chain, bf, sizeof(bf), false);

	if (symbol_conf.show_branchflag_count) {
		callchain_list_counts__printf_value(chain, NULL,
						    buf, sizeof(buf));

		if (asprintf(&alloc_str, "%s%s", str, buf) < 0)
			str = "Not enough memory!";
		else
			str = alloc_str;
	}

	fputs(str, fp);
	fputc('\n', fp);
	free(alloc_str);

	return ret;
}