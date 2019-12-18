#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int hasPrefix; int /*<<< orphan*/  nodeLabels; int /*<<< orphan*/  nNodes; int /*<<< orphan*/  prefixDatum; int /*<<< orphan*/  allTheSame; int /*<<< orphan*/  returnData; int /*<<< orphan*/  level; int /*<<< orphan*/  traversalValue; int /*<<< orphan*/  traversalMemoryContext; int /*<<< orphan*/  reconstructedValue; int /*<<< orphan*/  norderbys; int /*<<< orphan*/  nkeys; int /*<<< orphan*/  orderbys; int /*<<< orphan*/  scankeys; } ;
typedef  TYPE_1__ spgInnerConsistentIn ;
struct TYPE_14__ {scalar_t__ prefixSize; int /*<<< orphan*/  nNodes; int /*<<< orphan*/  allTheSame; } ;
struct TYPE_13__ {int /*<<< orphan*/  state; int /*<<< orphan*/  want_itup; int /*<<< orphan*/  traversalCxt; int /*<<< orphan*/  numberOfNonNullOrderBys; int /*<<< orphan*/  numberOfKeys; int /*<<< orphan*/  orderByData; int /*<<< orphan*/  keyData; } ;
struct TYPE_12__ {int /*<<< orphan*/  level; int /*<<< orphan*/  traversalValue; int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ SpGistSearchItem ;
typedef  TYPE_3__* SpGistScanOpaque ;
typedef  TYPE_4__* SpGistInnerTuple ;

/* Variables and functions */
 int /*<<< orphan*/  SGITDATUM (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spgExtractNodeLabels (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void
spgInitInnerConsistentIn(spgInnerConsistentIn *in,
						 SpGistScanOpaque so,
						 SpGistSearchItem *item,
						 SpGistInnerTuple innerTuple)
{
	in->scankeys = so->keyData;
	in->orderbys = so->orderByData;
	in->nkeys = so->numberOfKeys;
	in->norderbys = so->numberOfNonNullOrderBys;
	in->reconstructedValue = item->value;
	in->traversalMemoryContext = so->traversalCxt;
	in->traversalValue = item->traversalValue;
	in->level = item->level;
	in->returnData = so->want_itup;
	in->allTheSame = innerTuple->allTheSame;
	in->hasPrefix = (innerTuple->prefixSize > 0);
	in->prefixDatum = SGITDATUM(innerTuple, &so->state);
	in->nNodes = innerTuple->nNodes;
	in->nodeLabels = spgExtractNodeLabels(&so->state, innerTuple);
}