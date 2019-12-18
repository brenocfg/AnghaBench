#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; } ;
struct TYPE_7__ {TYPE_4__ special; scalar_t__ have_special_relative; } ;
struct TYPE_8__ {TYPE_1__ relative; } ;
typedef  TYPE_2__ timelib_time ;

/* Variables and functions */
#define  TIMELIB_SPECIAL_WEEKDAY 128 
 int /*<<< orphan*/  do_adjust_special_weekday (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timelib_do_normalize (TYPE_2__*) ; 

__attribute__((used)) static void do_adjust_special(timelib_time* time)
{
	if (time->relative.have_special_relative) {
		switch (time->relative.special.type) {
			case TIMELIB_SPECIAL_WEEKDAY:
				do_adjust_special_weekday(time);
				break;
		}
	}
	timelib_do_normalize(time);
	memset(&(time->relative.special), 0, sizeof(time->relative.special));
}