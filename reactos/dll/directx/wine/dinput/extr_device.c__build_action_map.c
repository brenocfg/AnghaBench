#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  guid; } ;
struct TYPE_11__ {int dwNumActions; int dwCRC; TYPE_1__* rgoAction; } ;
struct TYPE_10__ {int dwObjID; int dwSemantic; int /*<<< orphan*/  dwHow; int /*<<< orphan*/  guidInstance; } ;
typedef  int /*<<< orphan*/  LPDIRECTINPUTDEVICE8W ;
typedef  int /*<<< orphan*/ * LPDIOBJECTDATAFORMAT ;
typedef  TYPE_2__* LPDIACTIONFORMATW ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  LPCDIDATAFORMAT ;
typedef  TYPE_3__ IDirectInputDeviceImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DIAH_DEFAULT ; 
 int /*<<< orphan*/  DIAH_UNMAPPED ; 
 scalar_t__ DIDBAM_HWDEFAULTS ; 
 scalar_t__ DIDBAM_PRESERVE ; 
 scalar_t__ DIDFT_AXIS ; 
 scalar_t__ DIDFT_BUTTON ; 
 scalar_t__ DIDFT_GETINSTANCE (scalar_t__) ; 
 scalar_t__ DIDFT_GETTYPE (scalar_t__) ; 
 scalar_t__ DIDFT_PSHBUTTON ; 
 scalar_t__ DIDFT_RELAXIS ; 
 int /*<<< orphan*/  DI_NOEFFECT ; 
 int /*<<< orphan*/  DI_OK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetUserNameW (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IDirectInputDevice8WImpl_BuildActionMap (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int MAX_PATH ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * dataformat_to_odf_by_type (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_3__* impl_from_IDirectInputDevice8W (int /*<<< orphan*/ ) ; 
 scalar_t__ load_mapping_settings (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ semantic_to_obj_id (TYPE_3__*,scalar_t__) ; 

HRESULT _build_action_map(LPDIRECTINPUTDEVICE8W iface, LPDIACTIONFORMATW lpdiaf, LPCWSTR lpszUserName, DWORD dwFlags, DWORD devMask, LPCDIDATAFORMAT df)
{
    IDirectInputDeviceImpl *This = impl_from_IDirectInputDevice8W(iface);
    WCHAR username[MAX_PATH];
    DWORD username_size = MAX_PATH;
    int i;
    BOOL load_success = FALSE, has_actions = FALSE;

    /* Unless asked the contrary by these flags, try to load a previous mapping */
    if (!(dwFlags & DIDBAM_HWDEFAULTS))
    {
        /* Retrieve logged user name if necessary */
        if (lpszUserName == NULL)
            GetUserNameW(username, &username_size);
        else
            lstrcpynW(username, lpszUserName, MAX_PATH);

        load_success = load_mapping_settings(This, lpdiaf, username);
    }

    if (load_success) {
        /* Update dwCRC to track if action format has changed */
        for (i=0; i < lpdiaf->dwNumActions; i++)
        {
            lpdiaf->dwCRC ^= (lpdiaf->rgoAction[i].dwObjID << i * 2) | (lpdiaf->rgoAction[i].dwObjID >> (sizeof(lpdiaf->dwCRC) * 8 - i * 2));
            lpdiaf->dwCRC ^= (lpdiaf->rgoAction[i].dwSemantic << (i * 2 + 5)) | (lpdiaf->rgoAction[i].dwSemantic >> (sizeof(lpdiaf->dwCRC) * 8 - (i * 2 + 5)));
        }
        return DI_OK;
    }

    for (i=0; i < lpdiaf->dwNumActions; i++)
    {
        if ((lpdiaf->rgoAction[i].dwSemantic & devMask) == devMask)
        {
            DWORD obj_id = semantic_to_obj_id(This, lpdiaf->rgoAction[i].dwSemantic);
            DWORD type = DIDFT_GETTYPE(obj_id);
            DWORD inst = DIDFT_GETINSTANCE(obj_id);

            LPDIOBJECTDATAFORMAT odf;

            if (type == DIDFT_PSHBUTTON) type = DIDFT_BUTTON;
            if (type == DIDFT_RELAXIS) type = DIDFT_AXIS;

            /* Make sure the object exists */
            odf = dataformat_to_odf_by_type(df, inst, type);

            if (odf != NULL)
            {
                lpdiaf->rgoAction[i].dwObjID = obj_id;
                lpdiaf->rgoAction[i].guidInstance = This->guid;
                lpdiaf->rgoAction[i].dwHow = DIAH_DEFAULT;
                has_actions = TRUE;
            }
        }
        else if (!(dwFlags & DIDBAM_PRESERVE))
        {
            /* We must clear action data belonging to other devices */
            memset(&lpdiaf->rgoAction[i].guidInstance, 0, sizeof(GUID));
            lpdiaf->rgoAction[i].dwHow = DIAH_UNMAPPED;
        }
    }

    /* Update dwCRC to track if action format has changed */
    lpdiaf->dwCRC = 0;
    for (i=0; i < lpdiaf->dwNumActions; i++)
    {
        lpdiaf->dwCRC ^= (lpdiaf->rgoAction[i].dwObjID << i * 2) | (lpdiaf->rgoAction[i].dwObjID >> (sizeof(lpdiaf->dwCRC) * 8 - i * 2));
        lpdiaf->dwCRC ^= (lpdiaf->rgoAction[i].dwSemantic << (i * 2 + 5)) | (lpdiaf->rgoAction[i].dwSemantic >> (sizeof(lpdiaf->dwCRC) * 8 - (i * 2 + 5)));
    }

    if (!has_actions) return DI_NOEFFECT;

    return  IDirectInputDevice8WImpl_BuildActionMap(iface, lpdiaf, lpszUserName, dwFlags);
}