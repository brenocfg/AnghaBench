#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  latest_nodes; } ;
struct TYPE_5__ {scalar_t__ user; } ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_1__ RAnalEsil ;
typedef  TYPE_2__ EsilDataFlow ;

/* Variables and functions */
 int /*<<< orphan*/  edf_consume_2_set_reg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * sdb_ptr_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_remove (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edf_eq_weak (RAnalEsil *esil) {
	EsilDataFlow *edf = (EsilDataFlow *)esil->user;
	RGraphNode *o_old = sdb_ptr_get (edf->latest_nodes, "old", 0);	//node for esil->old
	RGraphNode *o_new = sdb_ptr_get (edf->latest_nodes, "new", 0);	//node for esil->cur
	if (!edf_consume_2_set_reg (esil, ":=")) {
		return 0;
	}
	//work-around
	if (o_old) {
		sdb_ptr_set (edf->latest_nodes, "old", o_old, 0);
	} else {
		sdb_remove (edf->latest_nodes, "old", 0);
	}
	if (o_new) {
		sdb_ptr_set (edf->latest_nodes, "new", o_new, 0);
	} else {
		sdb_remove (edf->latest_nodes, "new", 0);
	}
	return 1;
}