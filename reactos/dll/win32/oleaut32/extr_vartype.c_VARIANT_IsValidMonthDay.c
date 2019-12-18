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
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IsLeapYear (int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL VARIANT_IsValidMonthDay(DWORD day, DWORD month, DWORD year)
{
  static const BYTE days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  if (day && month && month < 13)
  {
    if (day <= days[month] || (month == 2 && day == 29 && IsLeapYear(year)))
      return TRUE;
  }
  return FALSE;
}