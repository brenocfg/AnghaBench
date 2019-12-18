#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* head; } ;
struct TYPE_9__ {int /*<<< orphan*/  curSub; TYPE_1__ towork; } ;
struct TYPE_8__ {int /*<<< orphan*/  next; } ;
typedef  TYPE_2__ ParsedLex ;
typedef  TYPE_3__ LexizeData ;

/* Variables and functions */
 int /*<<< orphan*/  RemoveHead (TYPE_3__*) ; 

__attribute__((used)) static void
moveToWaste(LexizeData *ld, ParsedLex *stop)
{
	bool		go = true;

	while (ld->towork.head && go)
	{
		if (ld->towork.head == stop)
		{
			ld->curSub = stop->next;
			go = false;
		}
		RemoveHead(ld);
	}
}