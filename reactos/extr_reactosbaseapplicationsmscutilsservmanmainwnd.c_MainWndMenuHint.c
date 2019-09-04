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
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {scalar_t__ CmdId; int /*<<< orphan*/  HintId; } ;
struct TYPE_5__ {int /*<<< orphan*/  hStatus; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  TYPE_2__ MENU_HINT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SB_SIMPLEID ; 
 int /*<<< orphan*/  StatusBarLoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static BOOL
MainWndMenuHint(PMAIN_WND_INFO Info,
                WORD CmdId,
                const MENU_HINT *HintArray,
                DWORD HintsCount,
                UINT DefHintId)
{
    BOOL Found = FALSE;
    const MENU_HINT *LastHint;
    UINT HintId = DefHintId;

    LastHint = HintArray + HintsCount;
    while (HintArray != LastHint)
    {
        if (HintArray->CmdId == CmdId)
        {
            HintId = HintArray->HintId;
            Found = TRUE;
            break;
        }
        HintArray++;
    }

    StatusBarLoadString(Info->hStatus,
                        SB_SIMPLEID,
                        hInstance,
                        HintId);

    return Found;
}