#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int bModesPruned; int bKeyIsReadOnly; int bPruningOn; TYPE_1__* DeskExtInterface; } ;
struct TYPE_5__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  (* GetPruningMode ) (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ;} ;
typedef  TYPE_2__* PDESKMONITOR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  UpdatePruningControls (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static VOID
GetPruningSettings(PDESKMONITOR This)
{
    BOOL bModesPruned = FALSE, bKeyIsReadOnly = FALSE, bPruningOn = FALSE;

    if (This->DeskExtInterface != NULL)
    {
        This->DeskExtInterface->GetPruningMode(This->DeskExtInterface->Context,
                                               &bModesPruned,
                                               &bKeyIsReadOnly,
                                               &bPruningOn);
    }

    /* Check the boolean values against zero before assigning it to the bitfields! */
    This->bModesPruned = (bModesPruned != FALSE);
    This->bKeyIsReadOnly = (bKeyIsReadOnly != FALSE);
    This->bPruningOn = (bPruningOn != FALSE);

    UpdatePruningControls(This);
}