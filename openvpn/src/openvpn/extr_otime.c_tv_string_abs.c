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
typedef  int /*<<< orphan*/  time_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 char const* time_string (int /*<<< orphan*/ ,long,int,struct gc_arena*) ; 

const char *
tv_string_abs(const struct timeval *tv, struct gc_arena *gc)
{
    return time_string((time_t) tv->tv_sec,
                       (long) tv->tv_usec,
                       true,
                       gc);
}