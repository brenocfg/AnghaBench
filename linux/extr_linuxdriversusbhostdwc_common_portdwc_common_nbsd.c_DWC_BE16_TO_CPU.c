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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

uint16_t DWC_BE16_TO_CPU(uint16_t *p)
{
#ifdef __BIG_ENDIAN
	return *p;
#else
	uint8_t *u_p = (uint8_t *)p;
	return (u_p[1] | (u_p[0] << 8));
#endif
}