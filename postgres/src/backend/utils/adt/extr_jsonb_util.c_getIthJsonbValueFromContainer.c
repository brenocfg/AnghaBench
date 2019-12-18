#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_7__ {int /*<<< orphan*/ * children; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_1__ JsonbContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  JsonContainerIsArray (TYPE_1__*) ; 
 size_t JsonContainerSize (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fillJsonbValue (TYPE_1__*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getJsonbOffset (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/ * palloc (int) ; 

JsonbValue *
getIthJsonbValueFromContainer(JsonbContainer *container, uint32 i)
{
	JsonbValue *result;
	char	   *base_addr;
	uint32		nelements;

	if (!JsonContainerIsArray(container))
		elog(ERROR, "not a jsonb array");

	nelements = JsonContainerSize(container);
	base_addr = (char *) &container->children[nelements];

	if (i >= nelements)
		return NULL;

	result = palloc(sizeof(JsonbValue));

	fillJsonbValue(container, i, base_addr,
				   getJsonbOffset(container, i),
				   result);

	return result;
}