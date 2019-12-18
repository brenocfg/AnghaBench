#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimeOffset ;
struct TYPE_4__ {int /*<<< orphan*/  time; scalar_t__ day; scalar_t__ month; } ;
typedef  TYPE_1__ Interval ;

/* Variables and functions */
 TYPE_1__* palloc (int) ; 

__attribute__((used)) static Interval *
offset_to_interval(TimeOffset offset)
{
	Interval   *result = palloc(sizeof(Interval));

	result->month = 0;
	result->day = 0;
	result->time = offset;

	return result;
}