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
typedef  int /*<<< orphan*/  float8 ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  DateADT ;

/* Variables and functions */
 int /*<<< orphan*/  Abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DateADTGetDatum (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_mi ; 

__attribute__((used)) static float8
gdb_date_dist(const void *a, const void *b, FmgrInfo *flinfo)
{
	/* we assume the difference can't overflow */
	Datum		diff = DirectFunctionCall2(date_mi,
										   DateADTGetDatum(*((const DateADT *) a)),
										   DateADTGetDatum(*((const DateADT *) b)));

	return (float8) Abs(DatumGetInt32(diff));
}