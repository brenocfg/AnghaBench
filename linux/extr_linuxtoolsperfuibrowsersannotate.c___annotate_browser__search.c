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
struct annotation_line {int dummy; } ;
struct annotate_browser {int searching_backwards; int /*<<< orphan*/  search_bf; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 struct annotation_line* annotate_browser__find_string (struct annotate_browser*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  annotate_browser__set_top (struct annotate_browser*,struct annotation_line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_helpline__puts (char*) ; 

__attribute__((used)) static bool __annotate_browser__search(struct annotate_browser *browser)
{
	struct annotation_line *al;
	s64 idx;

	al = annotate_browser__find_string(browser, browser->search_bf, &idx);
	if (al == NULL) {
		ui_helpline__puts("String not found!");
		return false;
	}

	annotate_browser__set_top(browser, al, idx);
	browser->searching_backwards = false;
	return true;
}