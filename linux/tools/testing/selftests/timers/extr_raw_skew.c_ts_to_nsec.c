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
struct timespec {int tv_sec; unsigned long long tv_nsec; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 

unsigned long long ts_to_nsec(struct timespec ts)
{
	return ts.tv_sec * NSEC_PER_SEC + ts.tv_nsec;
}