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
typedef  scalar_t__ u16 ;
struct ui_browser {scalar_t__ rows; scalar_t__ extra_title_lines; scalar_t__ index; scalar_t__ top_idx; } ;
struct perf_hpp_list {scalar_t__ nr_header_lines; } ;
struct hists {struct perf_hpp_list* hpp_list; } ;
struct hist_browser {int /*<<< orphan*/  show_headers; struct hists* hists; struct ui_browser b; } ;

/* Variables and functions */

__attribute__((used)) static void hist_browser__update_rows(struct hist_browser *hb)
{
	struct ui_browser *browser = &hb->b;
	struct hists *hists = hb->hists;
	struct perf_hpp_list *hpp_list = hists->hpp_list;
	u16 index_row;

	if (!hb->show_headers) {
		browser->rows += browser->extra_title_lines;
		browser->extra_title_lines = 0;
		return;
	}

	browser->extra_title_lines = hpp_list->nr_header_lines;
	browser->rows -= browser->extra_title_lines;
	/*
	 * Verify if we were at the last line and that line isn't
	 * visibe because we now show the header line(s).
	 */
	index_row = browser->index - browser->top_idx;
	if (index_row >= browser->rows)
		browser->index -= index_row - browser->rows + 1;
}