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
struct TYPE_3__ {int /*<<< orphan*/  BRbtnState; int /*<<< orphan*/  TLbtnState; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ PAGER_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ PGB_BOTTOMORRIGHT ; 
 scalar_t__ PGB_TOPORLEFT ; 
 int /*<<< orphan*/  PGF_INVISIBLE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LRESULT
PAGER_GetButtonState (const PAGER_INFO* infoPtr, INT btn)
{
    LRESULT btnState = PGF_INVISIBLE;
    TRACE("[%p]\n", infoPtr->hwndSelf);

    if (btn == PGB_TOPORLEFT)
        btnState = infoPtr->TLbtnState;
    else if (btn == PGB_BOTTOMORRIGHT)
        btnState = infoPtr->BRbtnState;

    return btnState;
}