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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_add_timeout (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  mp_time_us () ; 
 struct timespec mp_time_us_to_timespec (int /*<<< orphan*/ ) ; 

struct timespec mp_rel_time_to_timespec(double timeout_sec)
{
    return mp_time_us_to_timespec(mp_add_timeout(mp_time_us(), timeout_sec));
}