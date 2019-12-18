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
struct TYPE_3__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
typedef  TYPE_1__ mac8KEY ;
struct TYPE_4__ {scalar_t__ t; } ;
typedef  TYPE_2__ Nsrt ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Macaddr8PGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macaddr8_cmp ; 

__attribute__((used)) static int
gbt_macad8key_cmp(const void *a, const void *b, FmgrInfo *flinfo)
{
	mac8KEY    *ia = (mac8KEY *) (((const Nsrt *) a)->t);
	mac8KEY    *ib = (mac8KEY *) (((const Nsrt *) b)->t);
	int			res;

	res = DatumGetInt32(DirectFunctionCall2(macaddr8_cmp, Macaddr8PGetDatum(&ia->lower), Macaddr8PGetDatum(&ib->lower)));
	if (res == 0)
		return DatumGetInt32(DirectFunctionCall2(macaddr8_cmp, Macaddr8PGetDatum(&ia->upper), Macaddr8PGetDatum(&ib->upper)));

	return res;
}