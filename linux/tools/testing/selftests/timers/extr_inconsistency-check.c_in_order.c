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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static inline int in_order(struct timespec a, struct timespec b)
{
	/* use unsigned to avoid false positives on 2038 rollover */
	if ((unsigned long)a.tv_sec < (unsigned long)b.tv_sec)
		return 1;
	if ((unsigned long)a.tv_sec > (unsigned long)b.tv_sec)
		return 0;
	if (a.tv_nsec > b.tv_nsec)
		return 0;
	return 1;
}