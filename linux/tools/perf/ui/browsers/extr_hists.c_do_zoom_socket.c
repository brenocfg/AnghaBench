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
struct popup_action {int socket; } ;
struct hist_browser {TYPE_1__* hists; int /*<<< orphan*/  pstack; } ;
struct TYPE_3__ {int socket_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISTC_SOCKET ; 
 int /*<<< orphan*/  hist_browser__reset (struct hist_browser*) ; 
 int /*<<< orphan*/  hists__filter_by_socket (TYPE_1__*) ; 
 int /*<<< orphan*/  hists__has (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_hpp__set_elide (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pstack__push (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pstack__remove (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  socket ; 

__attribute__((used)) static int
do_zoom_socket(struct hist_browser *browser, struct popup_action *act)
{
	if (!hists__has(browser->hists, socket) || act->socket < 0)
		return 0;

	if (browser->hists->socket_filter > -1) {
		pstack__remove(browser->pstack, &browser->hists->socket_filter);
		browser->hists->socket_filter = -1;
		perf_hpp__set_elide(HISTC_SOCKET, false);
	} else {
		browser->hists->socket_filter = act->socket;
		perf_hpp__set_elide(HISTC_SOCKET, true);
		pstack__push(browser->pstack, &browser->hists->socket_filter);
	}

	hists__filter_by_socket(browser->hists);
	hist_browser__reset(browser);
	return 0;
}