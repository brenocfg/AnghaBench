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
struct TYPE_2__ {struct map* map; } ;
struct popup_action {int /*<<< orphan*/  fn; TYPE_1__ ms; } ;
struct map {int dummy; } ;
struct hist_browser {int /*<<< orphan*/  hists; } ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*) ; 
 int /*<<< orphan*/  do_browse_map ; 
 int /*<<< orphan*/  dso ; 
 int /*<<< orphan*/  hists__has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_map_opt(struct hist_browser *browser,
	    struct popup_action *act, char **optstr, struct map *map)
{
	if (!hists__has(browser->hists, dso) || map == NULL)
		return 0;

	if (asprintf(optstr, "Browse map details") < 0)
		return 0;

	act->ms.map = map;
	act->fn = do_browse_map;
	return 1;
}