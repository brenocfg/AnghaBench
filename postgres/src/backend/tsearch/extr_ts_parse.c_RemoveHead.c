#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ posDict; int /*<<< orphan*/  towork; int /*<<< orphan*/  waste; } ;
typedef  TYPE_1__ LexizeData ;

/* Variables and functions */
 int /*<<< orphan*/  LPLAddTail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPLRemoveHead (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
RemoveHead(LexizeData *ld)
{
	LPLAddTail(&ld->waste, LPLRemoveHead(&ld->towork));

	ld->posDict = 0;
}