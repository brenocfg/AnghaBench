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
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  MONTHCAL_Circle (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MONTHCAL_GetDayRect (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void MONTHCAL_CircleDay(const MONTHCAL_INFO *infoPtr, HDC hdc,
                               const SYSTEMTIME *date)
{
  RECT r;

  MONTHCAL_GetDayRect(infoPtr, date, &r, -1);
  MONTHCAL_Circle(infoPtr, hdc, &r);
}