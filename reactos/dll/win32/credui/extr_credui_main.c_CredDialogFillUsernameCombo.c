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
struct cred_dialog_params {int dwFlags; } ;
struct TYPE_6__ {int iItem; int /*<<< orphan*/ * pszText; int /*<<< orphan*/  mask; } ;
struct TYPE_5__ {scalar_t__ Type; int /*<<< orphan*/ * UserName; } ;
typedef  TYPE_1__* PCREDENTIALW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  size_t DWORD ;
typedef  TYPE_2__ COMBOBOXEXITEMW ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CBEIF_TEXT ; 
 int /*<<< orphan*/  CBEM_INSERTITEMW ; 
 int CREDUI_FLAGS_GENERIC_CREDENTIALS ; 
 scalar_t__ CRED_TYPE_GENERIC ; 
 int /*<<< orphan*/  CredEnumerateW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,TYPE_1__***) ; 
 int /*<<< orphan*/  CredFree (TYPE_1__**) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CredDialogFillUsernameCombo(HWND hwndUsername, const struct cred_dialog_params *params)
{
    DWORD count;
    DWORD i;
    PCREDENTIALW *credentials;

    if (!CredEnumerateW(NULL, 0, &count, &credentials))
        return;

    for (i = 0; i < count; i++)
    {
        COMBOBOXEXITEMW comboitem;
        DWORD j;
        BOOL duplicate = FALSE;

        if (!credentials[i]->UserName)
            continue;

        if (params->dwFlags & CREDUI_FLAGS_GENERIC_CREDENTIALS)
        {
            if (credentials[i]->Type != CRED_TYPE_GENERIC)
            {
                credentials[i]->UserName = NULL;
                continue;
            }
        }
        else if (credentials[i]->Type == CRED_TYPE_GENERIC)
        {
            credentials[i]->UserName = NULL;
            continue;
        }

        /* don't add another item with the same name if we've already added it */
        for (j = 0; j < i; j++)
            if (credentials[j]->UserName
                && !lstrcmpW(credentials[i]->UserName, credentials[j]->UserName))
            {
                duplicate = TRUE;
                break;
            }

        if (duplicate)
            continue;

        comboitem.mask = CBEIF_TEXT;
        comboitem.iItem = -1;
        comboitem.pszText = credentials[i]->UserName;
        SendMessageW(hwndUsername, CBEM_INSERTITEMW, 0, (LPARAM)&comboitem);
    }

    CredFree(credentials);
}