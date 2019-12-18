#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CallerFInfoFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  enum_lt ; 

__attribute__((used)) static bool
gbt_enumlt(const void *a, const void *b, FmgrInfo *flinfo)
{
	return DatumGetBool(
						CallerFInfoFunctionCall2(enum_lt, flinfo, InvalidOid, ObjectIdGetDatum(*((const Oid *) a)), ObjectIdGetDatum(*((const Oid *) b)))
		);
}