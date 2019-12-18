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
struct TYPE_3__ {int /*<<< orphan*/ * value; scalar_t__ next; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_1__ JsonValueListIterator ;
typedef  int /*<<< orphan*/  JsonValueList ;

/* Variables and functions */
 int /*<<< orphan*/ * lfirst (scalar_t__) ; 
 scalar_t__ lnext (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static JsonbValue *
JsonValueListNext(const JsonValueList *jvl, JsonValueListIterator *it)
{
	JsonbValue *result = it->value;

	if (it->next)
	{
		it->value = lfirst(it->next);
		it->next = lnext(it->list, it->next);
	}
	else
	{
		it->value = NULL;
	}

	return result;
}