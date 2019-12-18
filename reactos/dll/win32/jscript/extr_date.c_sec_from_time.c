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
typedef  int DOUBLE ;

/* Variables and functions */
 int NAN ; 
 int /*<<< orphan*/  floor (int) ; 
 int fmod (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isnan (int) ; 

__attribute__((used)) static inline DOUBLE sec_from_time(DOUBLE time)
{
    DOUBLE ret;

    if(isnan(time))
        return NAN;

    ret = fmod(floor(time/1000), 60);
    if(ret<0) ret += 60;

    return ret;
}