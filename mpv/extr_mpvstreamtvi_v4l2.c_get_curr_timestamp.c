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
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock_gettime (int,struct timespec*) ; 

__attribute__((used)) static long long get_curr_timestamp(int clk_id)
{
    struct timespec ts;
    clock_gettime(clk_id, &ts);
    return (long long)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}