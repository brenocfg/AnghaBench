#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut32 ;
struct TYPE_13__ {int /*<<< orphan*/  atoms; TYPE_3__* cfg; } ;
struct TYPE_9__ {scalar_t__ idx; } ;
struct TYPE_8__ {scalar_t__ idx; } ;
struct TYPE_12__ {TYPE_2__ last; TYPE_1__ first; } ;
struct TYPE_11__ {scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  g; } ;
typedef  TYPE_4__ RGraphNode ;
typedef  TYPE_5__ RAnalEsilBB ;
typedef  TYPE_6__ EsilCfgGen ;

/* Variables and functions */
 int /*<<< orphan*/  r_graph_del_node (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  r_id_storage_delete (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int _graphnode_delete_always_0_cmp(void *incoming, void *in, void *user) {
	EsilCfgGen *gen = (EsilCfgGen *)user;
	RGraphNode *delete_me = (RGraphNode *)in;
	RAnalEsilBB *delete_me_bb = (RAnalEsilBB *)delete_me->data;
	r_graph_del_node (gen->cfg->g, delete_me);
	ut32 id;
	for (id = delete_me_bb->first.idx; id <= delete_me_bb->last.idx; id++) {
		r_id_storage_delete (gen->atoms, id);
	}
	return 0;
}