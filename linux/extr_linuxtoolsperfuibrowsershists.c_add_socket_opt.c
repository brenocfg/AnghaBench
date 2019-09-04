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
struct popup_action {int socket; int /*<<< orphan*/  fn; } ;
struct hist_browser {TYPE_1__* hists; } ;
struct TYPE_2__ {int socket_filter; } ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char*,int) ; 
 int /*<<< orphan*/  do_zoom_socket ; 
 int /*<<< orphan*/  hists__has (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket ; 

__attribute__((used)) static int
add_socket_opt(struct hist_browser *browser, struct popup_action *act,
	       char **optstr, int socket_id)
{
	if (!hists__has(browser->hists, socket) || socket_id < 0)
		return 0;

	if (asprintf(optstr, "Zoom %s Processor Socket %d",
		     (browser->hists->socket_filter > -1) ? "out of" : "into",
		     socket_id) < 0)
		return 0;

	act->socket = socket_id;
	act->fn = do_zoom_socket;
	return 1;
}