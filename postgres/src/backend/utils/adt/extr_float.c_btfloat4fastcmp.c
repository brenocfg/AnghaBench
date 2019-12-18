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
typedef  int /*<<< orphan*/  float4 ;
typedef  int /*<<< orphan*/  SortSupport ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetFloat4 (int /*<<< orphan*/ ) ; 
 int float4_cmp_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
btfloat4fastcmp(Datum x, Datum y, SortSupport ssup)
{
	float4		arg1 = DatumGetFloat4(x);
	float4		arg2 = DatumGetFloat4(y);

	return float4_cmp_internal(arg1, arg2);
}