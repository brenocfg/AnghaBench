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

__attribute__((used)) static struct timeval php_openssl_subtract_timeval(struct timeval a, struct timeval b) /* {{{ */
{
	struct timeval difference;

	difference.tv_sec  = a.tv_sec  - b.tv_sec;
	difference.tv_usec = a.tv_usec - b.tv_usec;

	if (a.tv_usec < b.tv_usec) {
	  	b.tv_sec  -= 1L;
	   	b.tv_usec += 1000000L;
	}

	return difference;
}