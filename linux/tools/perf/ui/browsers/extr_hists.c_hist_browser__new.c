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
struct hists {int dummy; } ;
struct hist_browser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hist_browser__init (struct hist_browser*,struct hists*) ; 
 struct hist_browser* zalloc (int) ; 

struct hist_browser *hist_browser__new(struct hists *hists)
{
	struct hist_browser *browser = zalloc(sizeof(*browser));

	if (browser)
		hist_browser__init(browser, hists);

	return browser;
}