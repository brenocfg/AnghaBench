#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  TYPE_1__ tv ;

/* Variables and functions */

__attribute__((used)) static int timeval_subtract(tv *result, tv *end, tv *begin) {
	// Perform the carry for the later subtraction by updating Y
	if (end->tv_usec < begin->tv_usec) {
		int nsec = (begin->tv_usec - end->tv_usec) / 1000000 + 1;
		begin->tv_usec -= 1000000 * nsec;
		begin->tv_sec += nsec;
	}
	if (end->tv_usec - begin->tv_usec > 1000000) {
		int nsec = (end->tv_usec - begin->tv_usec) / 1000000;
		begin->tv_usec += 1000000 * nsec;
		begin->tv_sec -= nsec;
	}

	// Compute the time remaining to wait. 'tv_usec' is certainly positive.
	result->tv_sec = end->tv_sec - begin->tv_sec;
	result->tv_usec = end->tv_usec - begin->tv_usec;

	// Return 1 if result is negative
	return end->tv_sec < begin->tv_sec;
}