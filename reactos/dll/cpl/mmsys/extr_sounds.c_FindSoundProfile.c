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
struct TYPE_3__ {int /*<<< orphan*/  szName; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PSOUND_SCHEME_CONTEXT ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ CB_ERR ; 
 scalar_t__ ComboBox_GetCount (int /*<<< orphan*/ ) ; 
 scalar_t__ ComboBox_GetItemData (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SOUND_SCHEME ; 
 int /*<<< orphan*/  _tcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

PSOUND_SCHEME_CONTEXT FindSoundProfile(HWND hwndDlg, TCHAR * szName)
{
    LRESULT lCount, lIndex, lResult;
    PSOUND_SCHEME_CONTEXT pScheme;
    HWND hwndComboBox;

    hwndComboBox = GetDlgItem(hwndDlg, IDC_SOUND_SCHEME);
    lCount = ComboBox_GetCount(hwndComboBox);
    if (lCount == CB_ERR)
    {
        return NULL;
    }

    for (lIndex = 0; lIndex < lCount; lIndex++)
    {
        lResult = ComboBox_GetItemData(hwndComboBox, lIndex);
        if (lResult == CB_ERR)
        {
            continue;
        }

        pScheme = (PSOUND_SCHEME_CONTEXT)lResult;
        if (!_tcsicmp(pScheme->szName, szName))
        {
            return pScheme;
        }
    }
    return NULL;
}