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
struct timezone {int dummy; } ;
struct timespec64 {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec64 const*,struct timezone const*) ; 
 int /*<<< orphan*/  settime ; 

int security_settime64(const struct timespec64 *ts, const struct timezone *tz)
{
	return call_int_hook(settime, 0, ts, tz);
}