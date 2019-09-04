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
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static bool tv_leq(const struct timeval *a, const struct timeval *b)
{
	if (a->tv_sec != b->tv_sec)
		return a->tv_sec < b->tv_sec;
	else
		return a->tv_usec <= b->tv_usec;
}