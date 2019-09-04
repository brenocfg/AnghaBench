#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  title; int /*<<< orphan*/  body; } ;
typedef  TYPE_1__ RANode ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void agraph_print_node_dot(RANode *n, void *user) {
	char *label = strdup (n->body);
	//label = r_str_replace (label, "\n", "\\l", 1);
	if (!label || !*label) {
		r_cons_printf ("\"%s\" [URL=\"%s\", color=\"lightgray\", label=\"%s\"]\n",
				n->title, n->title, n->title);
	} else {
		r_cons_printf ("\"%s\" [URL=\"%s\", color=\"lightgray\", label=\"%s\\n%s\"]\n",
				n->title, n->title, n->title, label);
	}
	free (label);
}