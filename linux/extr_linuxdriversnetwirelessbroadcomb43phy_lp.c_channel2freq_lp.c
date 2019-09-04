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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline u16 channel2freq_lp(u8 channel)
{
	if (channel < 14)
		return (2407 + 5 * channel);
	else if (channel == 14)
		return 2484;
	else if (channel < 184)
		return (5000 + 5 * channel);
	else
		return (4000 + 5 * channel);
}