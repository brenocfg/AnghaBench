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
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 

__attribute__((used)) static inline uint64_t
timespec_to_ns(const struct timespec *ts)
{
        return ((uint64_t) ts->tv_sec * NSEC_PER_SEC) + ts->tv_nsec;
}