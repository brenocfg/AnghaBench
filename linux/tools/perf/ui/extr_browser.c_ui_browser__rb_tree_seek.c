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
struct ui_browser {struct rb_node* top; struct rb_root* entries; } ;
struct rb_root {int dummy; } ;
struct rb_node {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 struct rb_node* rb_first (struct rb_root*) ; 
 struct rb_node* rb_last (struct rb_root*) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct rb_node* rb_prev (struct rb_node*) ; 

void ui_browser__rb_tree_seek(struct ui_browser *browser, off_t offset, int whence)
{
	struct rb_root *root = browser->entries;
	struct rb_node *nd;

	switch (whence) {
	case SEEK_SET:
		nd = rb_first(root);
		break;
	case SEEK_CUR:
		nd = browser->top;
		break;
	case SEEK_END:
		nd = rb_last(root);
		break;
	default:
		return;
	}

	if (offset > 0) {
		while (offset-- != 0)
			nd = rb_next(nd);
	} else {
		while (offset++ != 0)
			nd = rb_prev(nd);
	}

	browser->top = nd;
}