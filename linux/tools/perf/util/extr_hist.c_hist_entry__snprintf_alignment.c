#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_hpp_fmt {int (* width ) (struct perf_hpp_fmt*,struct perf_hpp*,TYPE_2__*) ;int /*<<< orphan*/  list; } ;
struct perf_hpp {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct hist_entry {TYPE_2__* hists; } ;
struct TYPE_4__ {TYPE_1__* hpp_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance_hpp (struct perf_hpp*,int) ; 
 int /*<<< orphan*/  list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int scnprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int const,char*) ; 
 int stub1 (struct perf_hpp_fmt*,struct perf_hpp*,TYPE_2__*) ; 

int hist_entry__snprintf_alignment(struct hist_entry *he, struct perf_hpp *hpp,
				   struct perf_hpp_fmt *fmt, int printed)
{
	if (!list_is_last(&fmt->list, &he->hists->hpp_list->fields)) {
		const int width = fmt->width(fmt, hpp, he->hists);
		if (printed < width) {
			advance_hpp(hpp, printed);
			printed = scnprintf(hpp->buf, hpp->size, "%-*s", width - printed, " ");
		}
	}

	return printed;
}