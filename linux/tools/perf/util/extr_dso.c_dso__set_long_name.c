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
struct rb_root {int dummy; } ;
struct dso {int long_name_allocated; char const* long_name; int /*<<< orphan*/  long_name_len; struct rb_root* root; int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dsos__findnew_link_by_longname (struct rb_root*,struct dso*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,struct rb_root*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void dso__set_long_name(struct dso *dso, const char *name, bool name_allocated)
{
	struct rb_root *root = dso->root;

	if (name == NULL)
		return;

	if (dso->long_name_allocated)
		free((char *)dso->long_name);

	if (root) {
		rb_erase(&dso->rb_node, root);
		/*
		 * __dsos__findnew_link_by_longname() isn't guaranteed to add it
		 * back, so a clean removal is required here.
		 */
		RB_CLEAR_NODE(&dso->rb_node);
		dso->root = NULL;
	}

	dso->long_name		 = name;
	dso->long_name_len	 = strlen(name);
	dso->long_name_allocated = name_allocated;

	if (root)
		__dsos__findnew_link_by_longname(root, dso, NULL);
}