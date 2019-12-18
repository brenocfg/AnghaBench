#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int wDayOfWeek; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  MONTHCAL_CopyDate (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ st_null ; 

int MONTHCAL_CalculateDayOfWeek(SYSTEMTIME *date, BOOL inplace)
{
  SYSTEMTIME st = st_null;
  FILETIME ft;

  MONTHCAL_CopyDate(date, &st);

  SystemTimeToFileTime(&st, &ft);
  FileTimeToSystemTime(&ft, &st);

  if (inplace) date->wDayOfWeek = st.wDayOfWeek;

  return st.wDayOfWeek;
}