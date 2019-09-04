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
struct bcm_timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline ktime_t bcm_timeval_to_ktime(struct bcm_timeval tv)
{
	return ktime_set(tv.tv_sec, tv.tv_usec * NSEC_PER_USEC);
}