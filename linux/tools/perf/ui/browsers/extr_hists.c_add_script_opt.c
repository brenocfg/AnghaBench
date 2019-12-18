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
struct thread {int dummy; } ;
struct symbol {int dummy; } ;
struct popup_action {scalar_t__ time; } ;
struct hist_entry {scalar_t__ time; } ;
struct hist_browser {int dummy; } ;
struct evsel {int dummy; } ;
struct TYPE_2__ {scalar_t__ time_quantum; } ;

/* Variables and functions */
 int add_script_opt_2 (struct hist_browser*,struct popup_action*,char**,struct thread*,struct symbol*,struct evsel*,char*) ; 
 struct hist_entry* hist_browser__selected_entry (struct hist_browser*) ; 
 scalar_t__ sort_order ; 
 int sprintf (char*,char*) ; 
 scalar_t__ strstr (scalar_t__,char*) ; 
 TYPE_1__ symbol_conf ; 
 scalar_t__ timestamp__scnprintf_usec (scalar_t__,char*,int) ; 

__attribute__((used)) static int
add_script_opt(struct hist_browser *browser,
	       struct popup_action *act, char **optstr,
	       struct thread *thread, struct symbol *sym,
	       struct evsel *evsel)
{
	int n, j;
	struct hist_entry *he;

	n = add_script_opt_2(browser, act, optstr, thread, sym, evsel, "");

	he = hist_browser__selected_entry(browser);
	if (sort_order && strstr(sort_order, "time")) {
		char tstr[128];

		optstr++;
		act++;
		j = sprintf(tstr, " in ");
		j += timestamp__scnprintf_usec(he->time, tstr + j,
					       sizeof tstr - j);
		j += sprintf(tstr + j, "-");
		timestamp__scnprintf_usec(he->time + symbol_conf.time_quantum,
				          tstr + j, sizeof tstr - j);
		n += add_script_opt_2(browser, act, optstr, thread, sym,
					  evsel, tstr);
		act->time = he->time;
	}
	return n;
}