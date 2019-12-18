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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t w4rev(uint32_t const x)
{
	return   ((0xff & (x >> (0 * 8))) << (3 * 8))
	       | ((0xff & (x >> (1 * 8))) << (2 * 8))
	       | ((0xff & (x >> (2 * 8))) << (1 * 8))
	       | ((0xff & (x >> (3 * 8))) << (0 * 8));
}