#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hwndParent; } ;
struct TYPE_6__ {int /*<<< orphan*/  hwndNotify; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ HOTKEY_INFO ;
typedef  TYPE_2__ CREATESTRUCTW ;

/* Variables and functions */
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOTKEY_SetFont (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSTEM_FONT ; 

__attribute__((used)) static LRESULT
HOTKEY_Create (HOTKEY_INFO *infoPtr, const CREATESTRUCTW *lpcs)
{
    infoPtr->hwndNotify = lpcs->hwndParent;

    HOTKEY_SetFont(infoPtr, GetStockObject(SYSTEM_FONT), 0);

    return 0;
}