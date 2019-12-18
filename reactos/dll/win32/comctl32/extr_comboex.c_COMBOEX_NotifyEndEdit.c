#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ NtfUnicode; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  iWhy; int /*<<< orphan*/  szText; int /*<<< orphan*/  iNewSelection; int /*<<< orphan*/  fChanged; } ;
struct TYPE_7__ {int /*<<< orphan*/  iWhy; int /*<<< orphan*/  iNewSelection; int /*<<< orphan*/  fChanged; int /*<<< orphan*/  hdr; int /*<<< orphan*/  szText; } ;
typedef  TYPE_1__ NMCBEENDEDITW ;
typedef  TYPE_2__ NMCBEENDEDITA ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_3__ COMBOEX_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CBEMAXSTRLEN ; 
 int /*<<< orphan*/  CBEN_ENDEDITA ; 
 int /*<<< orphan*/  CBEN_ENDEDITW ; 
 int /*<<< orphan*/  COMBOEX_Notify (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT COMBOEX_NotifyEndEdit (const COMBOEX_INFO *infoPtr, NMCBEENDEDITW *neew, LPCWSTR wstr)
{
    /* Change the Text item from Unicode to ANSI if necessary for NOTIFY */
    if (infoPtr->NtfUnicode) {
	lstrcpynW(neew->szText, wstr, CBEMAXSTRLEN);
	return COMBOEX_Notify (infoPtr, CBEN_ENDEDITW, &neew->hdr);
    } else {
	NMCBEENDEDITA neea;

        neea.hdr = neew->hdr;
        neea.fChanged = neew->fChanged;
        neea.iNewSelection = neew->iNewSelection;
        WideCharToMultiByte (CP_ACP, 0, wstr, -1, neea.szText, CBEMAXSTRLEN, 0, 0);
        neea.iWhy = neew->iWhy;

        return COMBOEX_Notify (infoPtr, CBEN_ENDEDITA, &neea.hdr);
    }
}