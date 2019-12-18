#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int ti_options; int /*<<< orphan*/  mycid; int /*<<< orphan*/ * estate; int /*<<< orphan*/  cstate; scalar_t__ bufferedBytes; scalar_t__ bufferedTuples; int /*<<< orphan*/  multiInsertBuffers; } ;
struct TYPE_11__ {TYPE_2__* ri_RelationDesc; } ;
struct TYPE_10__ {TYPE_1__* rd_rel; } ;
struct TYPE_9__ {scalar_t__ relkind; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  CopyState ;
typedef  TYPE_4__ CopyMultiInsertInfo ;
typedef  int /*<<< orphan*/  CommandId ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMultiInsertInfoSetupBuffer (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  NIL ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 

__attribute__((used)) static void
CopyMultiInsertInfoInit(CopyMultiInsertInfo *miinfo, ResultRelInfo *rri,
						CopyState cstate, EState *estate, CommandId mycid,
						int ti_options)
{
	miinfo->multiInsertBuffers = NIL;
	miinfo->bufferedTuples = 0;
	miinfo->bufferedBytes = 0;
	miinfo->cstate = cstate;
	miinfo->estate = estate;
	miinfo->mycid = mycid;
	miinfo->ti_options = ti_options;

	/*
	 * Only setup the buffer when not dealing with a partitioned table.
	 * Buffers for partitioned tables will just be setup when we need to send
	 * tuples their way for the first time.
	 */
	if (rri->ri_RelationDesc->rd_rel->relkind != RELKIND_PARTITIONED_TABLE)
		CopyMultiInsertInfoSetupBuffer(miinfo, rri);
}