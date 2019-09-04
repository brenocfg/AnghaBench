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
typedef  scalar_t__ u64 ;
typedef  void* u32 ;
struct ui_browser {void* nr_entries; scalar_t__ top_idx; scalar_t__ index; int /*<<< orphan*/  (* seek ) (struct ui_browser*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * top; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  stub1 (struct ui_browser*,scalar_t__,int /*<<< orphan*/ ) ; 

void ui_browser__update_nr_entries(struct ui_browser *browser, u32 nr_entries)
{
	off_t offset = nr_entries - browser->nr_entries;

	browser->nr_entries = nr_entries;

	if (offset < 0) {
		if (browser->top_idx < (u64)-offset)
			offset = -browser->top_idx;

		browser->index += offset;
		browser->top_idx += offset;
	}

	browser->top = NULL;
	browser->seek(browser, browser->top_idx, SEEK_SET);
}