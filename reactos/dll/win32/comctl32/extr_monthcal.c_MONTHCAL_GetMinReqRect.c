#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_17__ {int /*<<< orphan*/  dwStyle; TYPE_2__ todayrect; TYPE_3__* calendars; } ;
struct TYPE_16__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; scalar_t__ bottom; } ;
struct TYPE_13__ {scalar_t__ bottom; } ;
struct TYPE_15__ {TYPE_1__ days; TYPE_4__ title; } ;
typedef  TYPE_4__ RECT ;
typedef  TYPE_5__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustWindowRect (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OffsetRect (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* wine_dbgstr_rect (TYPE_4__*) ; 

__attribute__((used)) static LRESULT
MONTHCAL_GetMinReqRect(const MONTHCAL_INFO *infoPtr, RECT *rect)
{
  TRACE("rect %p\n", rect);

  if(!rect) return FALSE;

  *rect = infoPtr->calendars[0].title;
  rect->bottom = infoPtr->calendars[0].days.bottom + infoPtr->todayrect.bottom -
                 infoPtr->todayrect.top;

  AdjustWindowRect(rect, infoPtr->dwStyle, FALSE);

  /* minimal rectangle is zero based */
  OffsetRect(rect, -rect->left, -rect->top);

  TRACE("%s\n", wine_dbgstr_rect(rect));

  return TRUE;
}