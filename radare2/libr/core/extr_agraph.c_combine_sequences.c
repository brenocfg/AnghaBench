#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct len_pos_t {int len; int pos; } ;
struct TYPE_17__ {TYPE_1__* layers; } ;
struct TYPE_16__ {int x; } ;
struct TYPE_15__ {void* free; } ;
struct TYPE_14__ {int /*<<< orphan*/ ** nodes; } ;
typedef  void* RListFree ;
typedef  TYPE_2__ RList ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_3__ RANode ;
typedef  TYPE_4__ RAGraph ;

/* Variables and functions */
 void* R_MAX (int,int) ; 
 void* R_MIN (int,int) ; 
 int /*<<< orphan*/  collect_changes (TYPE_4__ const*,int,int /*<<< orphan*/  const*,int,int,int,TYPE_2__*,int) ; 
 int dist_nodes (TYPE_4__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (struct len_pos_t*) ; 
 TYPE_3__* get_anode (int /*<<< orphan*/  const*) ; 
 scalar_t__ r_list_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  r_list_free (TYPE_2__*) ; 
 TYPE_2__* r_list_new () ; 
 scalar_t__ r_list_pop (TYPE_2__*) ; 

__attribute__((used)) static void combine_sequences(const RAGraph *g, int l, const RGraphNode *bm, const RGraphNode *bp, int from_up, int a, int r) {
	RList *Rm = r_list_new (), *Rp = r_list_new ();
	const RGraphNode *vt, *vtp;
	RANode *at, *atp;
	int rm, rp, t, m, i;
	Rm->free = (RListFree) free;
	Rp->free = (RListFree) free;

	t = (a + r) / 2;
	vt = g->layers[l].nodes[t - 1];
	vtp = g->layers[l].nodes[t];
	at = get_anode (vt);
	atp = get_anode (vtp);

	collect_changes (g, l, bm, from_up, a, t, Rm, true);
	collect_changes (g, l, bp, from_up, t, r, Rp, false);
	rm = rp = 0;

	m = dist_nodes (g, vt, vtp);
	if (at && atp) {
		while (atp->x - at->x < m) {
			if (atp->x == at->x) {
				int step = m / 2;
				at->x -= step;
				atp->x += m - step;
			} else {
				if (rm < rp) {
					if (r_list_empty (Rm)) {
						at->x = atp->x - m;
					} else {
						struct len_pos_t *cx = (struct len_pos_t *) r_list_pop (Rm);
						rm = rm + cx->len;
						at->x = R_MAX (cx->pos, atp->x - m);
						free (cx);
					}
				} else {
					if (r_list_empty (Rp)) {
						atp->x = at->x + m;
					} else {
						struct len_pos_t *cx = (struct len_pos_t *) r_list_pop (Rp);
						rp = rp + cx->len;
						atp->x = R_MIN (cx->pos, at->x + m);
						free (cx);
					}
				}
			}
		}
	}

	r_list_free (Rm);
	r_list_free (Rp);

	for (i = t - 2; i >= a; --i) {
		const RGraphNode *gv = g->layers[l].nodes[i];
		RANode *av = get_anode (gv);
		if (av && at) {
			av->x = R_MIN (av->x, at->x - dist_nodes (g, gv, vt));
		}
	}

	for (i = t + 1; i < r; ++i) {
		const RGraphNode *gv = g->layers[l].nodes[i];
		RANode *av = get_anode (gv);
		if (av && atp) {
			av->x = R_MAX (av->x, atp->x + dist_nodes (g, vtp, gv));
		}
	}
}