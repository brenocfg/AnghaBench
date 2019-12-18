#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum jbvType { ____Placeholder_jbvType } jbvType ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_1__ binary; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  JsonContainerIsScalar (int /*<<< orphan*/ ) ; 
 scalar_t__ jbvBinary ; 

__attribute__((used)) static JsonbValue *
getScalar(JsonbValue *scalar, enum jbvType type)
{
	/* Scalars should be always extracted during jsonpath execution. */
	Assert(scalar->type != jbvBinary ||
		   !JsonContainerIsScalar(scalar->val.binary.data));

	return scalar->type == type ? scalar : NULL;
}