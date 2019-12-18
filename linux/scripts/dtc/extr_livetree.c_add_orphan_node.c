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
struct property {int dummy; } ;
struct node {int dummy; } ;
struct data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_PHANDLE ; 
 int /*<<< orphan*/  TYPE_STRING ; 
 int /*<<< orphan*/  add_child (struct node*,struct node*) ; 
 struct node* build_node (struct property*,struct node*,int /*<<< orphan*/ *) ; 
 struct property* build_property (char*,struct data,int /*<<< orphan*/ *) ; 
 struct data data_add_marker (struct data,int /*<<< orphan*/ ,char*) ; 
 struct data data_append_data (struct data,char*,scalar_t__) ; 
 struct data data_append_integer (struct data,int,int) ; 
 struct data empty_data ; 
 int /*<<< orphan*/  name_node (struct node*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ) ; 

struct node * add_orphan_node(struct node *dt, struct node *new_node, char *ref)
{
	static unsigned int next_orphan_fragment = 0;
	struct node *node;
	struct property *p;
	struct data d = empty_data;
	char *name;

	if (ref[0] == '/') {
		d = data_add_marker(d, TYPE_STRING, ref);
		d = data_append_data(d, ref, strlen(ref) + 1);

		p = build_property("target-path", d, NULL);
	} else {
		d = data_add_marker(d, REF_PHANDLE, ref);
		d = data_append_integer(d, 0xffffffff, 32);

		p = build_property("target", d, NULL);
	}

	xasprintf(&name, "fragment@%u",
			next_orphan_fragment++);
	name_node(new_node, "__overlay__");
	node = build_node(p, new_node, NULL);
	name_node(node, name);

	add_child(dt, node);
	return dt;
}