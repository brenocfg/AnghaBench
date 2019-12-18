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
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (void const*) ; 
 int /*<<< orphan*/  macaddr_gt ; 

__attribute__((used)) static bool
gbt_macadgt(const void *a, const void *b, FmgrInfo *flinfo)
{
	return DatumGetBool(DirectFunctionCall2(macaddr_gt, PointerGetDatum(a), PointerGetDatum(b)));
}