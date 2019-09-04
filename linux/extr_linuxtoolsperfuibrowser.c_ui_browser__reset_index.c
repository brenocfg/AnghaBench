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
struct ui_browser {int /*<<< orphan*/  (* seek ) (struct ui_browser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ top_idx; scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  stub1 (struct ui_browser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ui_browser__reset_index(struct ui_browser *browser)
{
	browser->index = browser->top_idx = 0;
	browser->seek(browser, 0, SEEK_SET);
}