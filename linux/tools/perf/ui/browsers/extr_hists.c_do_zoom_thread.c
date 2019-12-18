#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {scalar_t__ comm_set; int /*<<< orphan*/  tid; } ;
struct popup_action {struct thread* thread; } ;
struct hist_browser {TYPE_1__* hists; int /*<<< orphan*/  pstack; } ;
struct TYPE_3__ {scalar_t__ thread_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISTC_THREAD ; 
 struct thread* comm ; 
 int /*<<< orphan*/  hist_browser__reset (struct hist_browser*) ; 
 int /*<<< orphan*/  hists__filter_by_thread (TYPE_1__*) ; 
 scalar_t__ hists__has (TYPE_1__*,struct thread*) ; 
 int /*<<< orphan*/  perf_hpp__set_elide (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pstack__push (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pstack__remove (int /*<<< orphan*/ ,scalar_t__*) ; 
 char* thread__comm_str (struct thread*) ; 
 scalar_t__ thread__get (struct thread*) ; 
 int /*<<< orphan*/  thread__zput (scalar_t__) ; 
 int /*<<< orphan*/  ui_helpline__fpush (char*,char*,...) ; 
 int /*<<< orphan*/  ui_helpline__pop () ; 

__attribute__((used)) static int
do_zoom_thread(struct hist_browser *browser, struct popup_action *act)
{
	struct thread *thread = act->thread;

	if ((!hists__has(browser->hists, thread) &&
	     !hists__has(browser->hists, comm)) || thread == NULL)
		return 0;

	if (browser->hists->thread_filter) {
		pstack__remove(browser->pstack, &browser->hists->thread_filter);
		perf_hpp__set_elide(HISTC_THREAD, false);
		thread__zput(browser->hists->thread_filter);
		ui_helpline__pop();
	} else {
		if (hists__has(browser->hists, thread)) {
			ui_helpline__fpush("To zoom out press ESC or ENTER + \"Zoom out of %s(%d) thread\"",
					   thread->comm_set ? thread__comm_str(thread) : "",
					   thread->tid);
		} else {
			ui_helpline__fpush("To zoom out press ESC or ENTER + \"Zoom out of %s thread\"",
					   thread->comm_set ? thread__comm_str(thread) : "");
		}

		browser->hists->thread_filter = thread__get(thread);
		perf_hpp__set_elide(HISTC_THREAD, false);
		pstack__push(browser->pstack, &browser->hists->thread_filter);
	}

	hists__filter_by_thread(browser->hists);
	hist_browser__reset(browser);
	return 0;
}