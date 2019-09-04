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
struct node {int dummy; } ;

/* Variables and functions */
 struct node* get_node_by_label (struct node*,char const*) ; 
 struct node* get_node_by_path (struct node*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

struct node *get_node_by_ref(struct node *tree, const char *ref)
{
	if (streq(ref, "/"))
		return tree;
	else if (ref[0] == '/')
		return get_node_by_path(tree, ref);
	else
		return get_node_by_label(tree, ref);
}