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
struct TYPE_4__ {int /*<<< orphan*/  todaySet; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 scalar_t__ MONTHCAL_UpdateToday (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
MONTHCAL_SetToday(MONTHCAL_INFO *infoPtr, const SYSTEMTIME *today)
{
  TRACE("%p\n", today);

  if (today)
  {
    /* remember if date was set successfully */
    if (MONTHCAL_UpdateToday(infoPtr, today)) infoPtr->todaySet = TRUE;
  }

  return 0;
}