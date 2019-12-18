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
struct TYPE_6__ {scalar_t__ user; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cur; int /*<<< orphan*/ * old; } ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_1__ RAnalEsilDFG ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  edf_consume_2_set_reg (TYPE_2__*) ; 

__attribute__((used)) static bool edf_eq_weak(RAnalEsil *esil) {
	RAnalEsilDFG *edf = (RAnalEsilDFG *)esil->user;
	RGraphNode *o_old = edf->old; //node for esil->old
	RGraphNode *o_new = edf->cur; //node for esil->cur
	if (!edf_consume_2_set_reg (esil)) {
		return false;
	}
	//work-around
	edf->old = o_old ? o_old : NULL;
	edf->cur = o_new ? o_new : NULL;
	return true;
}