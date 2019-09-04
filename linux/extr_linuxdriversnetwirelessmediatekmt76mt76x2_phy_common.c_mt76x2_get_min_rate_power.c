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
struct mt76_rate_power {int* all; } ;
typedef  int s8 ;

/* Variables and functions */
 int min (int,int) ; 

__attribute__((used)) static int
mt76x2_get_min_rate_power(struct mt76_rate_power *r)
{
	int i;
	s8 ret = 0;

	for (i = 0; i < sizeof(r->all); i++) {
		if (!r->all[i])
			continue;

		if (ret)
			ret = min(ret, r->all[i]);
		else
			ret = r->all[i];
	}

	return ret;
}