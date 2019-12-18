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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; scalar_t__ wMonth; scalar_t__ wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 scalar_t__ TM_YEAR_BASE ; 
 int /*<<< orphan*/  wceex_local_to_time_r (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

time_t wceex_local_to_time(const SYSTEMTIME *st)
{
    if (st == NULL)
    {
        return (time_t)-1;
    }
 
    return wceex_local_to_time_r(st->wYear - TM_YEAR_BASE,
                               st->wMonth - 1,
                               st->wDay, st->wHour,
                               st->wMinute,
                               st->wSecond);
}