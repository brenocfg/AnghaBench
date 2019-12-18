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
struct TYPE_3__ {int wMonth; scalar_t__ wDay; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MONTHCAL_MonthLength (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL MONTHCAL_ValidateDate(const SYSTEMTIME *time)
{
    if (time->wMonth < 1 || time->wMonth > 12 )
        return FALSE;
    if (time->wDay == 0 || time->wDay > MONTHCAL_MonthLength(time->wMonth, time->wYear))
        return FALSE;

    return TRUE;
}