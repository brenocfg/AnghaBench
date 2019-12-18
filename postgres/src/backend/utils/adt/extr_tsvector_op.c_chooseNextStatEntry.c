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
typedef  int uint32 ;
struct TYPE_4__ {int size; } ;
typedef  int /*<<< orphan*/  TSVectorStat ;
typedef  TYPE_1__* TSVector ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  insertStatEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static void
chooseNextStatEntry(MemoryContext persistentContext, TSVectorStat *stat, TSVector txt,
					uint32 low, uint32 high, uint32 offset)
{
	uint32		pos;
	uint32		middle = (low + high) >> 1;

	pos = (low + middle) >> 1;
	if (low != middle && pos >= offset && pos - offset < txt->size)
		insertStatEntry(persistentContext, stat, txt, pos - offset);
	pos = (high + middle + 1) >> 1;
	if (middle + 1 != high && pos >= offset && pos - offset < txt->size)
		insertStatEntry(persistentContext, stat, txt, pos - offset);

	if (low != middle)
		chooseNextStatEntry(persistentContext, stat, txt, low, middle, offset);
	if (high != middle + 1)
		chooseNextStatEntry(persistentContext, stat, txt, middle + 1, high, offset);
}