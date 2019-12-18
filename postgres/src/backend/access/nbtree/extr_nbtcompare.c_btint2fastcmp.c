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
typedef  scalar_t__ int16 ;
typedef  int /*<<< orphan*/  SortSupport ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetInt16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
btint2fastcmp(Datum x, Datum y, SortSupport ssup)
{
	int16		a = DatumGetInt16(x);
	int16		b = DatumGetInt16(y);

	return (int) a - (int) b;
}