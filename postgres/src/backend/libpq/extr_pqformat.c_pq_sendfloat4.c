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
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pq_sendfloat4(StringInfo buf, float4 f)
{
	union
	{
		float4		f;
		uint32		i;
	}			swap;

	swap.f = f;
	pq_sendint32(buf, swap.i);
}