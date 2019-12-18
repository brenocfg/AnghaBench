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
struct timespec {long long tv_sec; long long tv_nsec; } ;

/* Variables and functions */
 long long NSEC_PER_SEC ; 

struct timespec nsec_to_ts(long long ns)
{
	struct timespec ts;

	ts.tv_sec = ns/NSEC_PER_SEC;
	ts.tv_nsec = ns%NSEC_PER_SEC;
	return ts;
}