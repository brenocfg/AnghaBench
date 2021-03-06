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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ bInMenuLoop; int /*<<< orphan*/ * hStatus; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  SB_SIMPLE ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
UpdateMainStatusBar(PMAIN_WND_INFO Info)
{
    if (Info->hStatus != NULL)
    {
        SendMessage(Info->hStatus,
                    SB_SIMPLE,
                    (WPARAM)Info->bInMenuLoop,
                    0);
    }
}