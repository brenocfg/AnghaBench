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
struct property {int /*<<< orphan*/  name; } ;
struct node {int /*<<< orphan*/  fullpath; } ;
struct marker {scalar_t__ type; int /*<<< orphan*/  ref; int /*<<< orphan*/  offset; } ;
struct dt_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ REF_PHANDLE ; 
 int /*<<< orphan*/  append_to_property (struct node*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_fixup_entry(struct dt_info *dti, struct node *fn,
			    struct node *node, struct property *prop,
			    struct marker *m)
{
	char *entry;

	/* m->ref can only be a REF_PHANDLE, but check anyway */
	assert(m->type == REF_PHANDLE);

	/* there shouldn't be any ':' in the arguments */
	if (strchr(node->fullpath, ':') || strchr(prop->name, ':'))
		die("arguments should not contain ':'\n");

	xasprintf(&entry, "%s:%s:%u",
			node->fullpath, prop->name, m->offset);
	append_to_property(fn, m->ref, entry, strlen(entry) + 1);

	free(entry);
}