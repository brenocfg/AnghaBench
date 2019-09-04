#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct map* map; } ;
struct popup_action {TYPE_1__ ms; } ;
struct map {TYPE_2__* dso; } ;
struct hist_browser {TYPE_4__* hists; int /*<<< orphan*/  pstack; } ;
struct TYPE_8__ {TYPE_2__* dso_filter; } ;
struct TYPE_7__ {char* short_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISTC_DSO ; 
 scalar_t__ __map__is_kernel (struct map*) ; 
 int /*<<< orphan*/  dso ; 
 int /*<<< orphan*/  hist_browser__reset (struct hist_browser*) ; 
 int /*<<< orphan*/  hists__filter_by_dso (TYPE_4__*) ; 
 int /*<<< orphan*/  hists__has (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_hpp__set_elide (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pstack__push (int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  pstack__remove (int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  ui_helpline__fpush (char*,char*) ; 
 int /*<<< orphan*/  ui_helpline__pop () ; 

__attribute__((used)) static int
do_zoom_dso(struct hist_browser *browser, struct popup_action *act)
{
	struct map *map = act->ms.map;

	if (!hists__has(browser->hists, dso) || map == NULL)
		return 0;

	if (browser->hists->dso_filter) {
		pstack__remove(browser->pstack, &browser->hists->dso_filter);
		perf_hpp__set_elide(HISTC_DSO, false);
		browser->hists->dso_filter = NULL;
		ui_helpline__pop();
	} else {
		ui_helpline__fpush("To zoom out press ESC or ENTER + \"Zoom out of %s DSO\"",
				   __map__is_kernel(map) ? "the Kernel" : map->dso->short_name);
		browser->hists->dso_filter = map->dso;
		perf_hpp__set_elide(HISTC_DSO, true);
		pstack__push(browser->pstack, &browser->hists->dso_filter);
	}

	hists__filter_by_dso(browser->hists);
	hist_browser__reset(browser);
	return 0;
}