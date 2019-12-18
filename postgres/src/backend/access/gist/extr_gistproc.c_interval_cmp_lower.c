#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  float8 ;
struct TYPE_2__ {int /*<<< orphan*/  lower; } ;
typedef  TYPE_1__ SplitInterval ;

/* Variables and functions */
 int float8_cmp_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
interval_cmp_lower(const void *i1, const void *i2)
{
	float8		lower1 = ((const SplitInterval *) i1)->lower,
				lower2 = ((const SplitInterval *) i2)->lower;

	return float8_cmp_internal(lower1, lower2);
}