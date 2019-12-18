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
struct ptp_clock_time {long long sec; scalar_t__ nsec; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t pctns(struct ptp_clock_time *t)
{
	return t->sec * 1000000000LL + t->nsec;
}