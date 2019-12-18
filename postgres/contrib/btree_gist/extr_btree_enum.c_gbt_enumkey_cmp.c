#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ lower; scalar_t__ upper; } ;
typedef  TYPE_1__ oidKEY ;
struct TYPE_4__ {scalar_t__ t; } ;
typedef  TYPE_2__ Nsrt ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CallerFInfoFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  enum_cmp ; 

__attribute__((used)) static int
gbt_enumkey_cmp(const void *a, const void *b, FmgrInfo *flinfo)
{
	oidKEY	   *ia = (oidKEY *) (((const Nsrt *) a)->t);
	oidKEY	   *ib = (oidKEY *) (((const Nsrt *) b)->t);

	if (ia->lower == ib->lower)
	{
		if (ia->upper == ib->upper)
			return 0;

		return DatumGetInt32(
							 CallerFInfoFunctionCall2(enum_cmp, flinfo, InvalidOid, ObjectIdGetDatum(ia->upper), ObjectIdGetDatum(ib->upper))
			);
	}

	return DatumGetInt32(
						 CallerFInfoFunctionCall2(enum_cmp, flinfo, InvalidOid, ObjectIdGetDatum(ia->lower), ObjectIdGetDatum(ib->lower))
		);
}