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
typedef  int UCHAR ;

/* Variables and functions */

UCHAR kuhl_m_sr98_hid26_Manchester_4bits(UCHAR data4)
{
	UCHAR i, r;
	for(i = r = 0; i < 4; i++)
		r |= (1 << ((data4 >> i) & 1)) << (i * 2);
	return r;
}