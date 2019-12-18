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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  float8 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  pq_sendint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pq_sendfloat8(StringInfo buf, float8 f)
{
	union
	{
		float8		f;
		int64		i;
	}			swap;

	swap.f = f;
	pq_sendint64(buf, swap.i);
}