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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ lpButText; scalar_t__ lpMessText; scalar_t__ lpMessBox; scalar_t__ lpWinTxt; scalar_t__ lpAct; scalar_t__ lpInAct; int /*<<< orphan*/  hMenu; int /*<<< orphan*/  hMessageFont; int /*<<< orphan*/  hMenuFont; int /*<<< orphan*/  hCaptionFont; int /*<<< orphan*/  hbrWindow; int /*<<< orphan*/  hbrDesktop; int /*<<< orphan*/  hbrScrollbar; } ;
typedef  TYPE_1__* PPREVIEW_DATA ;
typedef  int /*<<< orphan*/  HLOCAL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
OnDestroy(PPREVIEW_DATA pPreviewData)
{
    DeleteObject(pPreviewData->hbrScrollbar);
    DeleteObject(pPreviewData->hbrDesktop);
    DeleteObject(pPreviewData->hbrWindow);

    DeleteObject(pPreviewData->hCaptionFont);
    DeleteObject(pPreviewData->hMenuFont);
    DeleteObject(pPreviewData->hMessageFont);

    DestroyMenu(pPreviewData->hMenu);

    LocalFree((HLOCAL)pPreviewData->lpInAct);
    LocalFree((HLOCAL)pPreviewData->lpAct);
    LocalFree((HLOCAL)pPreviewData->lpWinTxt);
    LocalFree((HLOCAL)pPreviewData->lpMessBox);
    LocalFree((HLOCAL)pPreviewData->lpMessText);
    LocalFree((HLOCAL)pPreviewData->lpButText);
}