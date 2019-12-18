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
struct TYPE_6__ {int /*<<< orphan*/  attLabelType; int /*<<< orphan*/  attPrefixType; int /*<<< orphan*/  attLeafType; int /*<<< orphan*/  attType; int /*<<< orphan*/  config; } ;
struct TYPE_5__ {int isBuild; int /*<<< orphan*/  myXid; int /*<<< orphan*/  deadTupleStorage; int /*<<< orphan*/  attLabelType; int /*<<< orphan*/  attPrefixType; int /*<<< orphan*/  attLeafType; int /*<<< orphan*/  attType; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ SpGistState ;
typedef  TYPE_2__ SpGistCache ;
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 int /*<<< orphan*/  GetTopTransactionIdIfAny () ; 
 int /*<<< orphan*/  SGDTSIZE ; 
 int /*<<< orphan*/  palloc0 (int /*<<< orphan*/ ) ; 
 TYPE_2__* spgGetCache (int /*<<< orphan*/ ) ; 

void
initSpGistState(SpGistState *state, Relation index)
{
	SpGistCache *cache;

	/* Get cached static information about index */
	cache = spgGetCache(index);

	state->config = cache->config;
	state->attType = cache->attType;
	state->attLeafType = cache->attLeafType;
	state->attPrefixType = cache->attPrefixType;
	state->attLabelType = cache->attLabelType;

	/* Make workspace for constructing dead tuples */
	state->deadTupleStorage = palloc0(SGDTSIZE);

	/* Set XID to use in redirection tuples */
	state->myXid = GetTopTransactionIdIfAny();

	/* Assume we're not in an index build (spgbuild will override) */
	state->isBuild = false;
}