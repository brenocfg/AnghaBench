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
struct data {int dummy; } ;
struct property {struct data val; } ;
struct node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_property (struct node*,struct property*) ; 
 struct property* build_property (char*,struct data) ; 
 struct data data_append_data (struct data,void const*,int) ; 
 struct data empty_data ; 
 struct property* get_property (struct node*,char*) ; 

void append_to_property(struct node *node,
				    char *name, const void *data, int len)
{
	struct data d;
	struct property *p;

	p = get_property(node, name);
	if (p) {
		d = data_append_data(p->val, data, len);
		p->val = d;
	} else {
		d = data_append_data(empty_data, data, len);
		p = build_property(name, d);
		add_property(node, p);
	}
}