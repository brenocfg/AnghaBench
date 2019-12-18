#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_11__ {TYPE_1__* tools; } ;
struct TYPE_10__ {scalar_t__ cbSize; char* lpszText; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpszText; } ;
typedef  TYPE_2__ TTTOOLINFOW ;
typedef  TYPE_3__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int INFOTIPSIZE ; 
 int /*<<< orphan*/  MAX_TEXT_SIZE_A ; 
 int /*<<< orphan*/  TOOLTIPS_GetTipText (TYPE_3__ const*,int,char*) ; 
 int TOOLTIPS_GetToolFromInfoT (TYPE_3__ const*,TYPE_2__*) ; 
 scalar_t__ TTTOOLINFOW_V1_SIZE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_GetTextT (const TOOLTIPS_INFO *infoPtr, TTTOOLINFOW *ti, BOOL isW)
{
    INT nTool;

    if (!ti) return 0;
    if (ti->cbSize < TTTOOLINFOW_V1_SIZE)
	return 0;

    nTool = TOOLTIPS_GetToolFromInfoT (infoPtr, ti);
    if (nTool == -1) return 0;

    if (infoPtr->tools[nTool].lpszText == NULL)
	return 0;

    if (isW) {
        ti->lpszText[0] = '\0';
        TOOLTIPS_GetTipText(infoPtr, nTool, ti->lpszText);
    }
    else {
        WCHAR buffer[INFOTIPSIZE];

        /* NB this API is broken, there is no way for the app to determine
           what size buffer it requires nor a way to specify how long the
           one it supplies is.  According to the test result, it's up to
           80 bytes by the ANSI version. */

        buffer[0] = '\0';
        TOOLTIPS_GetTipText(infoPtr, nTool, buffer);
        WideCharToMultiByte(CP_ACP, 0, buffer, -1, (LPSTR)ti->lpszText,
                                                   MAX_TEXT_SIZE_A, NULL, NULL);
    }

    return 0;
}