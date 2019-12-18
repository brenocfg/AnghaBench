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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  float4 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  pq_getmsgint (int /*<<< orphan*/ ,int) ; 

float4
pq_getmsgfloat4(StringInfo msg)
{
	union
	{
		float4		f;
		uint32		i;
	}			swap;

	swap.i = pq_getmsgint(msg, 4);
	return swap.f;
}