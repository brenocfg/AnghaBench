#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hMF; int /*<<< orphan*/  mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__* LPMETAFILEPICT ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CF_METAFILEPICT ; 
 int /*<<< orphan*/  GetClipboardData (int /*<<< orphan*/ ) ; 
 scalar_t__ GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlayMetaFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetViewportExtEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetViewportOrgEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void PlayMetaFileFromClipboard(HDC hdc, const RECT *lpRect)
{
    LPMETAFILEPICT mp;
    HGLOBAL hGlobal;

    hGlobal = GetClipboardData(CF_METAFILEPICT);
    if (!hGlobal)
        return;

    mp = (LPMETAFILEPICT)GlobalLock(hGlobal);
    if (!mp)
        return;

    SetMapMode(hdc, mp->mm);
    SetViewportExtEx(hdc, lpRect->right, lpRect->bottom, NULL);
    SetViewportOrgEx(hdc, lpRect->left, lpRect->top, NULL);
    PlayMetaFile(hdc, mp->hMF);
    GlobalUnlock(hGlobal);
}