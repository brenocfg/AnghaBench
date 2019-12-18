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
struct TYPE_3__ {int dwStyle; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int TBSTYLE_REGISTERDROP ; 

__attribute__((used)) static void
TOOLBAR_CheckStyle (const TOOLBAR_INFO *infoPtr)
{
    if (infoPtr->dwStyle & TBSTYLE_REGISTERDROP)
	FIXME("[%p] TBSTYLE_REGISTERDROP not implemented\n", infoPtr->hwndSelf);
}