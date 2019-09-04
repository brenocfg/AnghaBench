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
struct timeval {int tv_sec; unsigned long long tv_usec; } ;

/* Variables and functions */
 unsigned long long clk ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long long end_clock() {
    struct timeval tv;
    if(unlikely(gettimeofday(&tv, NULL) == -1))
        return -1;
    return clk = tv.tv_sec  * 1000000 + tv.tv_usec - clk;
}