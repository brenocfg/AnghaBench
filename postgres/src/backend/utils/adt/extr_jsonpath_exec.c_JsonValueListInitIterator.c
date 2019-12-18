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
struct TYPE_6__ {scalar_t__ list; int /*<<< orphan*/ * singleton; } ;
struct TYPE_5__ {scalar_t__ list; int /*<<< orphan*/ * next; int /*<<< orphan*/ * value; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_1__ JsonValueListIterator ;
typedef  TYPE_2__ JsonValueList ;

/* Variables and functions */
 scalar_t__ NIL ; 
 scalar_t__ linitial (scalar_t__) ; 
 int /*<<< orphan*/ * list_second_cell (scalar_t__) ; 

__attribute__((used)) static void
JsonValueListInitIterator(const JsonValueList *jvl, JsonValueListIterator *it)
{
	if (jvl->singleton)
	{
		it->value = jvl->singleton;
		it->list = NIL;
		it->next = NULL;
	}
	else if (jvl->list != NIL)
	{
		it->value = (JsonbValue *) linitial(jvl->list);
		it->list = jvl->list;
		it->next = list_second_cell(jvl->list);
	}
	else
	{
		it->value = NULL;
		it->list = NIL;
		it->next = NULL;
	}
}