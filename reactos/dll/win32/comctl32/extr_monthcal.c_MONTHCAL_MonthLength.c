#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int wMonth; int wYear; } ;

/* Variables and functions */
 TYPE_1__ min_allowed_date ; 

int MONTHCAL_MonthLength(int month, int year)
{
  const int mdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  /* Wrap around, this eases handling. Getting length only we shouldn't care
     about year change here cause January and December have
     the same day quantity */
  if(month == 0)
    month = 12;
  else if(month == 13)
    month = 1;

  /* special case for calendar transition year */
  if(month == min_allowed_date.wMonth && year == min_allowed_date.wYear) return 19;

  /* if we have a leap year add 1 day to February */
  /* a leap year is a year either divisible by 400 */
  /* or divisible by 4 and not by 100 */
  if(month == 2) { /* February */
    return mdays[month - 1] + ((year%400 == 0) ? 1 : ((year%100 != 0) &&
     (year%4 == 0)) ? 1 : 0);
  }
  else {
    return mdays[month - 1];
  }
}