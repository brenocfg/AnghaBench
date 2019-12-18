#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
struct TYPE_6__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct TYPE_7__ {int /*<<< orphan*/ * tmpRes; int /*<<< orphan*/ * lastRes; TYPE_1__ waste; int /*<<< orphan*/ * curSub; TYPE_2__ towork; scalar_t__ posDict; int /*<<< orphan*/  curDictId; int /*<<< orphan*/ * cfg; } ;
typedef  int /*<<< orphan*/  TSConfigCacheEntry ;
typedef  TYPE_3__ LexizeData ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 

__attribute__((used)) static void
LexizeInit(LexizeData *ld, TSConfigCacheEntry *cfg)
{
	ld->cfg = cfg;
	ld->curDictId = InvalidOid;
	ld->posDict = 0;
	ld->towork.head = ld->towork.tail = ld->curSub = NULL;
	ld->waste.head = ld->waste.tail = NULL;
	ld->lastRes = NULL;
	ld->tmpRes = NULL;
}