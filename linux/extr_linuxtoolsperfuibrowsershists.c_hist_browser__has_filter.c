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
struct hist_browser {scalar_t__ c2c_filter; scalar_t__ min_pcnt; int /*<<< orphan*/  hists; } ;
struct TYPE_2__ {scalar_t__ has_filter; } ;

/* Variables and functions */
 scalar_t__ hists__has_filter (int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static bool hist_browser__has_filter(struct hist_browser *hb)
{
	return hists__has_filter(hb->hists) || hb->min_pcnt || symbol_conf.has_filter || hb->c2c_filter;
}