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
struct TYPE_9__ {int /*<<< orphan*/  attbyval; } ;
struct TYPE_10__ {TYPE_1__ attLeafType; } ;
struct TYPE_12__ {TYPE_2__ state; } ;
struct TYPE_11__ {struct TYPE_11__* traversalValue; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ SpGistSearchItem ;
typedef  TYPE_4__* SpGistScanOpaque ;

/* Variables and functions */
 TYPE_3__* DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

__attribute__((used)) static void
spgFreeSearchItem(SpGistScanOpaque so, SpGistSearchItem *item)
{
	if (!so->state.attLeafType.attbyval &&
		DatumGetPointer(item->value) != NULL)
		pfree(DatumGetPointer(item->value));

	if (item->traversalValue)
		pfree(item->traversalValue);

	pfree(item);
}