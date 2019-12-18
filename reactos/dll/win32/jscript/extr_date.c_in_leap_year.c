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
typedef  int /*<<< orphan*/  DOUBLE ;

/* Variables and functions */
 int days_in_year (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  year_from_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int in_leap_year(DOUBLE time)
{
    if(days_in_year(year_from_time(time))==366)
        return 1;
    return 0;
}