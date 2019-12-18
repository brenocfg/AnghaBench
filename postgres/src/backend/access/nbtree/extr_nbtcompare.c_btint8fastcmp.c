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
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  SortSupport ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int A_GREATER_THAN_B ; 
 int A_LESS_THAN_B ; 
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
btint8fastcmp(Datum x, Datum y, SortSupport ssup)
{
	int64		a = DatumGetInt64(x);
	int64		b = DatumGetInt64(y);

	if (a > b)
		return A_GREATER_THAN_B;
	else if (a == b)
		return 0;
	else
		return A_LESS_THAN_B;
}