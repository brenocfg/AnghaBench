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
struct perf_top {scalar_t__ zero; } ;
struct hist_browser_timer {struct perf_top* arg; } ;
struct hist_browser {int /*<<< orphan*/  hists; struct hist_browser_timer* hbt; } ;

/* Variables and functions */
 int __hists__scnprintf_title (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  is_report_browser (struct hist_browser_timer*) ; 
 scalar_t__ scnprintf (char*,size_t,char*) ; 

__attribute__((used)) static int hists_browser__scnprintf_title(struct hist_browser *browser, char *bf, size_t size)
{
	struct hist_browser_timer *hbt = browser->hbt;
	int printed = __hists__scnprintf_title(browser->hists, bf, size, !is_report_browser(hbt));

	if (!is_report_browser(hbt)) {
		struct perf_top *top = hbt->arg;

		if (top->zero)
			printed += scnprintf(bf + printed, size - printed, " [z]");
	}

	return printed;
}