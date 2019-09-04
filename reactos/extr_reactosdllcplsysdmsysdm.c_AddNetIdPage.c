#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PROPSHEETHEADER ;
typedef  int /*<<< orphan*/ * (* PCreateNetIDPropertyPage ) () ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HPROPSHEETPAGE ;
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyPropertySheetPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PropSheetAddPage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char*) ; 

__attribute__((used)) static HMODULE
AddNetIdPage(PROPSHEETHEADER *ppsh)
{
    HPROPSHEETPAGE hPage;
    HMODULE hMod;
    PCreateNetIDPropertyPage pCreateNetIdPage;

    hMod = LoadLibrary(TEXT("netid.dll"));
    if (hMod != NULL)
    {
        pCreateNetIdPage = (PCreateNetIDPropertyPage)GetProcAddress(hMod,
                                                                    "CreateNetIDPropertyPage");
        if (pCreateNetIdPage != NULL)
        {
            hPage = pCreateNetIdPage();
            if (hPage == NULL)
                goto Fail;

            if (!PropSheetAddPage(hPage, (LPARAM)ppsh))
            {
                DestroyPropertySheetPage(hPage);
                goto Fail;
            }
        }
        else
        {
Fail:
            FreeLibrary(hMod);
            hMod = NULL;
        }
    }

    return hMod;
}