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
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;
typedef  int /*<<< orphan*/  RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 

__attribute__((used)) static int get_cgnodes(RAGraph *g, RCore *core, RAnalFunction *fcn) {
#if FCN_OLD
	RAnalFunction *f = r_anal_get_fcn_in (core->anal, core->offset, 0);
	RANode *node, *fcn_anode;
	RListIter *iter;
	RAnalRef *ref;
	RList *refs;
	if (!f) {
		return false;
	}
	if (!fcn) {
		fcn = f;
	}

	r_core_seek (core, f->addr, 1);

	char *title = get_title (fcn->addr);
	fcn_anode = r_agraph_add_node (g, title, "");

	free (title);
	if (!fcn_anode) {
		return false;
	}

	fcn_anode->x = 10;
	fcn_anode->y = 3;

	refs = r_anal_fcn_get_refs (core->anal, fcn);
	r_list_foreach (refs, iter, ref) {
		title = get_title (ref->addr);
		if (r_agraph_get_node (g, title) != NULL) {
			continue;
		}
		free (title);

		int size = 0;
		RAnalBlock *bb = r_anal_bb_from_offset (core->anal, ref->addr);
		if (bb) {
			size = bb->size;
		}

		char *body = get_body (core, ref->addr, size, mode2opts (g));
		title = get_title (ref->addr);

		node = r_agraph_add_node (g, title, body);
		if (!node) {
			return false;
		}

		free (title);
		free (body);

		node->x = 10;
		node->y = 10;

		r_agraph_add_edge (g, fcn_anode, node);
	}
	r_list_free (refs);
#else
	eprintf ("Must be sdbized\n");
#endif
	return true;
}