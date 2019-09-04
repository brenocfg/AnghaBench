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
struct hist_browser {int dummy; } ;
struct TYPE_2__ {scalar_t__ report_hierarchy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hists_browser__headers (struct hist_browser*) ; 
 int /*<<< orphan*/  hists_browser__hierarchy_headers (struct hist_browser*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static void hist_browser__show_headers(struct hist_browser *browser)
{
	if (symbol_conf.report_hierarchy)
		hists_browser__hierarchy_headers(browser);
	else
		hists_browser__headers(browser);
}