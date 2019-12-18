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
typedef  int /*<<< orphan*/  SortSupport ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int float8_cmp_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
btfloat8fastcmp(Datum x, Datum y, SortSupport ssup)
{
	float8		arg1 = DatumGetFloat8(x);
	float8		arg2 = DatumGetFloat8(y);

	return float8_cmp_internal(arg1, arg2);
}