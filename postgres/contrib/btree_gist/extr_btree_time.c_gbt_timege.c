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
typedef  int /*<<< orphan*/  TimeADT ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TimeADTGetDatumFast (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  time_ge ; 

__attribute__((used)) static bool
gbt_timege(const void *a, const void *b, FmgrInfo *flinfo)
{
	const TimeADT *aa = (const TimeADT *) a;
	const TimeADT *bb = (const TimeADT *) b;

	return DatumGetBool(DirectFunctionCall2(time_ge,
											TimeADTGetDatumFast(*aa),
											TimeADTGetDatumFast(*bb)));
}