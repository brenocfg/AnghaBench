#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  title; TYPE_1__* gnode; } ;
struct TYPE_4__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_2__ RANode ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void agraph_print_node_gml(RANode *n, void *user) {
	r_cons_printf ("  node [\n"
		"    id  %d\n"
		"    label  \"%s\"\n"
		"  ]\n", n->gnode->idx, n->title);
}