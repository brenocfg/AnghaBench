#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ginstate; } ;
struct TYPE_3__ {int /*<<< orphan*/  category; int /*<<< orphan*/  key; int /*<<< orphan*/  attnum; } ;
typedef  int /*<<< orphan*/  RBTNode ;
typedef  TYPE_1__ GinEntryAccumulator ;
typedef  TYPE_2__ BuildAccumulator ;

/* Variables and functions */
 int ginCompareAttEntries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmpEntryAccumulator(const RBTNode *a, const RBTNode *b, void *arg)
{
	const GinEntryAccumulator *ea = (const GinEntryAccumulator *) a;
	const GinEntryAccumulator *eb = (const GinEntryAccumulator *) b;
	BuildAccumulator *accum = (BuildAccumulator *) arg;

	return ginCompareAttEntries(accum->ginstate,
								ea->attnum, ea->key, ea->category,
								eb->attnum, eb->key, eb->category);
}