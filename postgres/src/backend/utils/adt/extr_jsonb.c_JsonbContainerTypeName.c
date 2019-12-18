#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_1__ JsonbContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ JsonContainerIsArray (TYPE_1__*) ; 
 scalar_t__ JsonContainerIsObject (TYPE_1__*) ; 
 scalar_t__ JsonbExtractScalar (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char const* JsonbTypeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
JsonbContainerTypeName(JsonbContainer *jbc)
{
	JsonbValue	scalar;

	if (JsonbExtractScalar(jbc, &scalar))
		return JsonbTypeName(&scalar);
	else if (JsonContainerIsArray(jbc))
		return "array";
	else if (JsonContainerIsObject(jbc))
		return "object";
	else
	{
		elog(ERROR, "invalid jsonb container type: 0x%08x", jbc->header);
		return "unknown";
	}
}