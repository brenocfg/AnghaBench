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

/* Variables and functions */
 scalar_t__ isdigit (unsigned char) ; 

__attribute__((used)) static unsigned
weight_checkdig(char *isn, unsigned size)
{
	unsigned	weight = 0;

	while (*isn && size > 1)
	{
		if (isdigit((unsigned char) *isn))
		{
			weight += size-- * (*isn - '0');
		}
		isn++;
	}
	weight = weight % 11;
	if (weight != 0)
		weight = 11 - weight;
	return weight;
}