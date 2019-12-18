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
struct hists {int /*<<< orphan*/ * thread_filter; } ;
struct hist_entry {int filtered; int /*<<< orphan*/ * thread; } ;

/* Variables and functions */
 int HIST_FILTER__THREAD ; 

__attribute__((used)) static bool hists__filter_entry_by_thread(struct hists *hists,
					  struct hist_entry *he)
{
	if (hists->thread_filter != NULL &&
	    he->thread != hists->thread_filter) {
		he->filtered |= (1 << HIST_FILTER__THREAD);
		return true;
	}

	return false;
}