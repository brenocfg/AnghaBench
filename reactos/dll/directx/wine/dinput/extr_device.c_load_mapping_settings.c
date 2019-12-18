#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  didev ;
typedef  char WCHAR ;
struct TYPE_11__ {int dwSize; int /*<<< orphan*/  guidInstance; int /*<<< orphan*/  tszInstanceName; } ;
struct TYPE_10__ {int /*<<< orphan*/  IDirectInputDevice8W_iface; } ;
struct TYPE_9__ {int dwNumActions; TYPE_1__* rgoAction; int /*<<< orphan*/  guidActionMap; } ;
struct TYPE_8__ {int dwObjID; int /*<<< orphan*/  dwHow; int /*<<< orphan*/  guidInstance; int /*<<< orphan*/  dwSemantic; } ;
typedef  TYPE_2__* LPDIACTIONFORMATW ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  TYPE_3__ IDirectInputDeviceImpl ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  TYPE_4__ DIDEVICEINSTANCEW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 int /*<<< orphan*/  DIAH_UNMAPPED ; 
 int /*<<< orphan*/  DIAH_USERCONFIG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirectInputDevice8_GetDeviceInfo (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StringFromCLSID (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_mapping_key (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ) ; 

BOOL load_mapping_settings(IDirectInputDeviceImpl *This, LPDIACTIONFORMATW lpdiaf, const WCHAR *username)
{
    HKEY hkey;
    WCHAR *guid_str;
    DIDEVICEINSTANCEW didev;
    int i;

    didev.dwSize = sizeof(didev);
    IDirectInputDevice8_GetDeviceInfo(&This->IDirectInputDevice8W_iface, &didev);

    if (StringFromCLSID(&lpdiaf->guidActionMap, &guid_str) != S_OK)
        return FALSE;

    hkey = get_mapping_key(didev.tszInstanceName, username, guid_str, FALSE);

    if (!hkey)
    {
        CoTaskMemFree(guid_str);
        return FALSE;
    }

    /* Try to read each action in the DIACTIONFORMAT from registry */
    for (i = 0; i < lpdiaf->dwNumActions; i++)
    {
        static const WCHAR format[] = {'%','x','\0'};
        DWORD id, size = sizeof(DWORD);
        WCHAR label[9];

        sprintfW(label, format, lpdiaf->rgoAction[i].dwSemantic);

        if (!RegQueryValueExW(hkey, label, 0, NULL, (LPBYTE) &id, &size))
        {
            lpdiaf->rgoAction[i].dwObjID = id;
            lpdiaf->rgoAction[i].guidInstance = didev.guidInstance;
            lpdiaf->rgoAction[i].dwHow = DIAH_USERCONFIG;
        }
        else
        {
            memset(&lpdiaf->rgoAction[i].guidInstance, 0, sizeof(GUID));
            lpdiaf->rgoAction[i].dwHow = DIAH_UNMAPPED;
        }

    }

    RegCloseKey(hkey);
    CoTaskMemFree(guid_str);

    /* On Windows BuildActionMap can open empty mapping, so always return TRUE if get_mapping_key is success */
    return TRUE;
}