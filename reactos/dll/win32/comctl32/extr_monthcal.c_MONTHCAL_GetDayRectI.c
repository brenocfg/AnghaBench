#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t width_increment; size_t height_increment; scalar_t__ textHeight; TYPE_1__* calendars; } ;
struct TYPE_9__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_8__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_7__ {TYPE_2__ days; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ MONTHCAL_INFO ;
typedef  size_t INT ;

/* Variables and functions */

__attribute__((used)) static inline void MONTHCAL_GetDayRectI(const MONTHCAL_INFO *infoPtr, RECT *r,
  INT col, INT row, INT calIdx)
{
  r->left   = infoPtr->calendars[calIdx].days.left + col * infoPtr->width_increment;
  r->right  = r->left + infoPtr->width_increment;
  r->top    = infoPtr->calendars[calIdx].days.top  + row * infoPtr->height_increment;
  r->bottom = r->top + infoPtr->textHeight;
}