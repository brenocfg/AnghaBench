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

/* Variables and functions */
 scalar_t__ float4_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ float4_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
float4_cmp_internal(float4 a, float4 b)
{
	if (float4_gt(a, b))
		return 1;
	if (float4_lt(a, b))
		return -1;
	return 0;
}