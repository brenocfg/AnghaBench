#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut32 ;
struct TYPE_15__ {int /*<<< orphan*/  blocks; int /*<<< orphan*/  atoms; } ;
struct TYPE_11__ {scalar_t__ idx; } ;
struct TYPE_10__ {scalar_t__ idx; } ;
struct TYPE_14__ {int /*<<< orphan*/  expr; TYPE_2__ last; TYPE_1__ first; } ;
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_12__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_3__ RGraphVisitor ;
typedef  TYPE_4__ RGraphNode ;
typedef  TYPE_5__ RAnalEsilBB ;
typedef  TYPE_6__ EsilCfgGen ;

/* Variables and functions */
 int /*<<< orphan*/  _graphnode_esilbb_insert_cmp ; 
 scalar_t__ r_id_storage_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ r_id_storage_take (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r_rbtree_cont_delete (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  r_strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

void _round_2_cb (RGraphNode *n, RGraphVisitor *vi) {
	RAnalEsilBB *bb = (RAnalEsilBB *)n->data;
	EsilCfgGen *gen = (EsilCfgGen *)vi->data;
	RStrBuf *buf = r_strbuf_new ((char *)r_id_storage_get (gen->atoms, bb->first.idx));
	r_strbuf_append (buf, ",");
	ut32 id;
	for (id = bb->first.idx + 1; id <= bb->last.idx; id++) {
		// use r_id_storage_take here to start fini for the atoms
		r_strbuf_appendf (buf, "%s,", (char *)r_id_storage_take (gen->atoms, id));
	}
	bb->expr = strdup (r_strbuf_get (buf));
	r_strbuf_free (buf);
	r_rbtree_cont_delete (gen->blocks, n, _graphnode_esilbb_insert_cmp, NULL);
}