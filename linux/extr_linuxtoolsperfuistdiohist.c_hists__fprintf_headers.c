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
struct perf_hpp {char* buf; int size; } ;
struct hists {int dummy; } ;
typedef  int /*<<< orphan*/  bf ;
struct TYPE_2__ {scalar_t__ report_hierarchy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int hists__fprintf_hierarchy_headers (struct hists*,struct perf_hpp*,int /*<<< orphan*/ *) ; 
 int hists__fprintf_standard_headers (struct hists*,struct perf_hpp*,int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 

int hists__fprintf_headers(struct hists *hists, FILE *fp)
{
	char bf[1024];
	struct perf_hpp dummy_hpp = {
		.buf	= bf,
		.size	= sizeof(bf),
	};

	fprintf(fp, "# ");

	if (symbol_conf.report_hierarchy)
		return hists__fprintf_hierarchy_headers(hists, &dummy_hpp, fp);
	else
		return hists__fprintf_standard_headers(hists, &dummy_hpp, fp);

}