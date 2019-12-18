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
struct TYPE_7__ {int /*<<< orphan*/ * tail; TYPE_2__* head; } ;
struct TYPE_9__ {TYPE_1__ waste; } ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_2__ ParsedLex ;
typedef  TYPE_3__ LexizeData ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
setCorrLex(LexizeData *ld, ParsedLex **correspondLexem)
{
	if (correspondLexem)
	{
		*correspondLexem = ld->waste.head;
	}
	else
	{
		ParsedLex  *tmp,
				   *ptr = ld->waste.head;

		while (ptr)
		{
			tmp = ptr->next;
			pfree(ptr);
			ptr = tmp;
		}
	}
	ld->waste.head = ld->waste.tail = NULL;
}