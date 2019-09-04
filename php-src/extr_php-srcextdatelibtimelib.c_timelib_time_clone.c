#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tz_info; scalar_t__ tz_abbr; } ;
typedef  TYPE_1__ timelib_time ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ timelib_strdup (scalar_t__) ; 
 TYPE_1__* timelib_time_ctor () ; 

timelib_time* timelib_time_clone(timelib_time *orig)
{
	timelib_time *tmp = timelib_time_ctor();
	memcpy(tmp, orig, sizeof(timelib_time));
	if (orig->tz_abbr) {
		tmp->tz_abbr = timelib_strdup(orig->tz_abbr);
	}
	if (orig->tz_info) {
		tmp->tz_info = orig->tz_info;
	}
	return tmp;
}