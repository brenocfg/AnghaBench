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

__attribute__((used)) static void reg_split(unsigned long long variable, unsigned int *high,
	unsigned int *low)
{
	*low = (unsigned int)variable & 0xFFFFFFFF;
	*high = (unsigned int)(variable >> 32);
}