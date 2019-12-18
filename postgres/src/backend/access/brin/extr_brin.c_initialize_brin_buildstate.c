#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bs_bdesc; int /*<<< orphan*/  bs_dtuple; int /*<<< orphan*/ * bs_rmAccess; scalar_t__ bs_currRangeStart; int /*<<< orphan*/  bs_pagesPerRange; int /*<<< orphan*/  bs_currentInsertBuf; scalar_t__ bs_numtuples; int /*<<< orphan*/  bs_irel; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  BrinRevmap ;
typedef  TYPE_1__ BrinBuildState ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  brin_build_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_memtuple_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_new_memtuple (int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc (int) ; 

__attribute__((used)) static BrinBuildState *
initialize_brin_buildstate(Relation idxRel, BrinRevmap *revmap,
						   BlockNumber pagesPerRange)
{
	BrinBuildState *state;

	state = palloc(sizeof(BrinBuildState));

	state->bs_irel = idxRel;
	state->bs_numtuples = 0;
	state->bs_currentInsertBuf = InvalidBuffer;
	state->bs_pagesPerRange = pagesPerRange;
	state->bs_currRangeStart = 0;
	state->bs_rmAccess = revmap;
	state->bs_bdesc = brin_build_desc(idxRel);
	state->bs_dtuple = brin_new_memtuple(state->bs_bdesc);

	brin_memtuple_initialize(state->bs_dtuple, state->bs_bdesc);

	return state;
}