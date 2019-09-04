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
typedef  int suseconds_t ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 struct timespec ns_to_timespec (int /*<<< orphan*/  const) ; 

struct timeval ns_to_timeval(const s64 nsec)
{
	struct timespec ts = ns_to_timespec(nsec);
	struct timeval tv;

	tv.tv_sec = ts.tv_sec;
	tv.tv_usec = (suseconds_t) ts.tv_nsec / 1000;

	return tv;
}