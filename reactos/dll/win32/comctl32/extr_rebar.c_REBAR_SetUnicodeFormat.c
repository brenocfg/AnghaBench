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
struct TYPE_3__ {scalar_t__ bUnicode; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  scalar_t__ LRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline LRESULT
REBAR_SetUnicodeFormat (REBAR_INFO *infoPtr, BOOL unicode)
{
    BOOL bTemp = infoPtr->bUnicode;

    TRACE("to %s hwnd=%p, was %s\n",
	   unicode ? "TRUE" : "FALSE", infoPtr->hwndSelf,
	  (bTemp) ? "TRUE" : "FALSE");

    infoPtr->bUnicode = unicode;

   return bTemp;
}