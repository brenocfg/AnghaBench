#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int y; int m; int d; int /*<<< orphan*/ * tz_info; scalar_t__ us; scalar_t__ s; scalar_t__ i; scalar_t__ h; } ;
typedef  TYPE_1__ timelib_time ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timelib_time_reset_fields(timelib_time *time)
{
	assert(time != NULL);

	time->y = 1970;
	time->m = 1;
	time->d = 1;
	time->h = time->i = time->s = 0;
	time->us = 0;
	time->tz_info = NULL;
}