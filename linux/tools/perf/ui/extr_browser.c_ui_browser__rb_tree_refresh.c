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
struct ui_browser {int rows; int /*<<< orphan*/  (* write ) (struct ui_browser*,struct rb_node*,int) ;struct rb_node* top; int /*<<< orphan*/  entries; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 struct rb_node* rb_first (int /*<<< orphan*/ ) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 int /*<<< orphan*/  stub1 (struct ui_browser*,struct rb_node*,int) ; 
 int /*<<< orphan*/  ui_browser__gotorc (struct ui_browser*,int,int /*<<< orphan*/ ) ; 

unsigned int ui_browser__rb_tree_refresh(struct ui_browser *browser)
{
	struct rb_node *nd;
	int row = 0;

	if (browser->top == NULL)
                browser->top = rb_first(browser->entries);

	nd = browser->top;

	while (nd != NULL) {
		ui_browser__gotorc(browser, row, 0);
		browser->write(browser, nd, row);
		if (++row == browser->rows)
			break;
		nd = rb_next(nd);
	}

	return row;
}