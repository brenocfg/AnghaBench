#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_5__ {int bias; int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DateInstance ;
typedef  int /*<<< orphan*/  DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  date_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int daylight_saving_ta (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  local_time (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static HRESULT dateobj_to_string(DateInstance *date, jsval_t *r)
{
    DOUBLE time;
    int offset;

    time = local_time(date->time, date);
    offset = date->bias +
        daylight_saving_ta(time, date);

    return date_to_string(time, TRUE, offset, r);
}