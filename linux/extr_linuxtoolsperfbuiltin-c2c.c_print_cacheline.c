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
struct perf_hpp_list {int dummy; } ;
struct perf_hpp {char* buf; int size; } ;
struct hist_entry {int dummy; } ;
struct c2c_hists {int /*<<< orphan*/  hists; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __hist_entry__snprintf (struct hist_entry*,struct perf_hpp*,struct perf_hpp_list*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hists__fprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hists__fprintf_headers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_cacheline(struct c2c_hists *c2c_hists,
			    struct hist_entry *he_cl,
			    struct perf_hpp_list *hpp_list,
			    FILE *out)
{
	char bf[1000];
	struct perf_hpp hpp = {
		.buf            = bf,
		.size           = 1000,
	};
	static bool once;

	if (!once) {
		hists__fprintf_headers(&c2c_hists->hists, out);
		once = true;
	} else {
		fprintf(out, "\n");
	}

	fprintf(out, "  -------------------------------------------------------------\n");
	__hist_entry__snprintf(he_cl, &hpp, hpp_list);
	fprintf(out, "%s\n", bf);
	fprintf(out, "  -------------------------------------------------------------\n");

	hists__fprintf(&c2c_hists->hists, false, 0, 0, 0, out, false);
}