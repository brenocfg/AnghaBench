#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int wDay; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  MONTHCAL_CompareSystemTime (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  MONTHCAL_CopyDate (TYPE_1__ const*,TYPE_1__*) ; 
 TYPE_1__ st_null ; 

__attribute__((used)) static LONG MONTHCAL_CompareMonths(const SYSTEMTIME *first, const SYSTEMTIME *second)
{
  SYSTEMTIME st_first, st_second;

  st_first = st_second = st_null;
  MONTHCAL_CopyDate(first, &st_first);
  MONTHCAL_CopyDate(second, &st_second);
  st_first.wDay = st_second.wDay = 1;

  return MONTHCAL_CompareSystemTime(&st_first, &st_second);
}