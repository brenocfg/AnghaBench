#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wintrust_data ;
typedef  int /*<<< orphan*/  fileInfo ;
struct TYPE_8__ {int member_0; int /*<<< orphan*/  hFile; int /*<<< orphan*/  pcwszFilePath; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_2__ WINTRUST_FILE_INFO ;
struct TYPE_7__ {TYPE_2__* pFile; } ;
struct TYPE_9__ {int member_0; int /*<<< orphan*/  dwUIChoice; int /*<<< orphan*/  dwUnionChoice; TYPE_1__ u; TYPE_4__* pSIPClientData; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_3__ WINTRUST_DATA ;
struct TYPE_10__ {int /*<<< orphan*/  hFile; int /*<<< orphan*/  lpPath; } ;
typedef  TYPE_4__* LPWIN_TRUST_SUBJECT_FILE ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINTRUST_DefaultVerifyAndClose (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  WTD_CHOICE_FILE ; 
 int /*<<< orphan*/  WTD_UI_NONE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG WINTRUST_PublishedSoftware(HWND hwnd, GUID *actionID,
 WINTRUST_DATA *data)
{
    WINTRUST_DATA wintrust_data = { sizeof(wintrust_data), 0 };
    /* Undocumented: the published software action is passed a path,
     * and pSIPClientData points to a WIN_TRUST_SUBJECT_FILE.
     */
    LPWIN_TRUST_SUBJECT_FILE subjectFile = data->pSIPClientData;
    WINTRUST_FILE_INFO fileInfo = { sizeof(fileInfo), 0 };

    TRACE("subjectFile->hFile: %p\n", subjectFile->hFile);
    TRACE("subjectFile->lpPath: %s\n", debugstr_w(subjectFile->lpPath));
    fileInfo.pcwszFilePath = subjectFile->lpPath;
    fileInfo.hFile = subjectFile->hFile;
    wintrust_data.u.pFile = &fileInfo;
    wintrust_data.dwUnionChoice = WTD_CHOICE_FILE;
    wintrust_data.dwUIChoice = WTD_UI_NONE;

    return WINTRUST_DefaultVerifyAndClose(hwnd, actionID, &wintrust_data);
}