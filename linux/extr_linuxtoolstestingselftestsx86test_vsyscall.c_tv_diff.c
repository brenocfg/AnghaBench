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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static double tv_diff(const struct timeval *a, const struct timeval *b)
{
	return (double)(a->tv_sec - b->tv_sec) +
		(double)((int)a->tv_usec - (int)b->tv_usec) * 1e-6;
}