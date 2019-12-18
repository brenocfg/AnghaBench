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
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {TYPE_1__ binary; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbContainer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ JsonContainerIsArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonContainerIsScalar (int /*<<< orphan*/ *) ; 
 int JsonContainerSize (int /*<<< orphan*/ *) ; 
 scalar_t__ jbvArray ; 
 scalar_t__ jbvBinary ; 

__attribute__((used)) static int
JsonbArraySize(JsonbValue *jb)
{
	Assert(jb->type != jbvArray);

	if (jb->type == jbvBinary)
	{
		JsonbContainer *jbc = jb->val.binary.data;

		if (JsonContainerIsArray(jbc) && !JsonContainerIsScalar(jbc))
			return JsonContainerSize(jbc);
	}

	return -1;
}