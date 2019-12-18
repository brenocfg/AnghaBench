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
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TV_WITHIN_SIGMA_MAX_SEC ; 
 int tv_subtract (struct timeval const*,struct timeval const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
tv_within_sigma(const struct timeval *t1, const struct timeval *t2, unsigned int sigma)
{
    const int delta = tv_subtract(t1, t2, TV_WITHIN_SIGMA_MAX_SEC); /* sigma should be less than 10 minutes */
    return -(int)sigma <= delta && delta <= (int)sigma;
}