#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  db; int /*<<< orphan*/  is_callgraph; } ;
struct TYPE_9__ {TYPE_2__* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  graph_false; int /*<<< orphan*/  graph_true; int /*<<< orphan*/  graph_box3; int /*<<< orphan*/  graph_box2; int /*<<< orphan*/  graph_box; } ;
struct TYPE_8__ {TYPE_1__ pal; } ;
typedef  TYPE_3__ RCons ;
typedef  TYPE_4__ RAGraph ;

/* Variables and functions */
 TYPE_3__* r_cons_singleton () ; 
 int /*<<< orphan*/  sdb_bool_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_set_enc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void agraph_sdb_init(const RAGraph *g) {
	sdb_bool_set (g->db, "agraph.is_callgraph", g->is_callgraph, 0);
	RCons *cons = r_cons_singleton ();
	sdb_set_enc (g->db, "agraph.color_box", cons->context->pal.graph_box, 0);
	sdb_set_enc (g->db, "agraph.color_box2", cons->context->pal.graph_box2, 0);
	sdb_set_enc (g->db, "agraph.color_box3", cons->context->pal.graph_box3, 0);
	sdb_set_enc (g->db, "agraph.color_true", cons->context->pal.graph_true, 0);
	sdb_set_enc (g->db, "agraph.color_false", cons->context->pal.graph_false, 0);
}