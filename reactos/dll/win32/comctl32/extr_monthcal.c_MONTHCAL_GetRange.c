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
struct TYPE_3__ {int /*<<< orphan*/  rangeValid; int /*<<< orphan*/  minDate; int /*<<< orphan*/  maxDate; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
MONTHCAL_GetRange(const MONTHCAL_INFO *infoPtr, SYSTEMTIME *range)
{
  TRACE("%p\n", range);

  if (!range) return 0;

  range[1] = infoPtr->maxDate;
  range[0] = infoPtr->minDate;

  return infoPtr->rangeValid;
}