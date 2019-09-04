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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t w8rev(uint64_t const x)
{
	return   ((0xff & (x >> (0 * 8))) << (7 * 8))
	       | ((0xff & (x >> (1 * 8))) << (6 * 8))
	       | ((0xff & (x >> (2 * 8))) << (5 * 8))
	       | ((0xff & (x >> (3 * 8))) << (4 * 8))
	       | ((0xff & (x >> (4 * 8))) << (3 * 8))
	       | ((0xff & (x >> (5 * 8))) << (2 * 8))
	       | ((0xff & (x >> (6 * 8))) << (1 * 8))
	       | ((0xff & (x >> (7 * 8))) << (0 * 8));
}