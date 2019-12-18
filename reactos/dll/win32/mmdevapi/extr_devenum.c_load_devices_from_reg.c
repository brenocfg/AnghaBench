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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  pwszVal; } ;
struct TYPE_5__ {scalar_t__ vt; TYPE_1__ u; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  int /*<<< orphan*/  PROPERTYKEY ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVICE_STATE_NOTPRESENT ; 
 int /*<<< orphan*/  DEVPKEY_Device_FriendlyName ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int KEY_READ ; 
 int KEY_WOW64_64KEY ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  MMDevice_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMDevice_GetPropValue (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VT_EMPTY ; 
 scalar_t__ VT_LPWSTR ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int eCapture ; 
 int eRender ; 
 int /*<<< orphan*/ * key_capture ; 
 int /*<<< orphan*/ * key_render ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_capture ; 
 int /*<<< orphan*/  reg_render ; 
 int /*<<< orphan*/  software_mmdevapi ; 

__attribute__((used)) static HRESULT load_devices_from_reg(void)
{
    DWORD i = 0;
    HKEY root, cur;
    LONG ret;
    DWORD curflow;

    ret = RegCreateKeyExW(HKEY_LOCAL_MACHINE, software_mmdevapi, 0, NULL, 0, KEY_WRITE|KEY_READ|KEY_WOW64_64KEY, NULL, &root, NULL);
    if (ret == ERROR_SUCCESS)
        ret = RegCreateKeyExW(root, reg_capture, 0, NULL, 0, KEY_READ|KEY_WRITE|KEY_WOW64_64KEY, NULL, &key_capture, NULL);
    if (ret == ERROR_SUCCESS)
        ret = RegCreateKeyExW(root, reg_render, 0, NULL, 0, KEY_READ|KEY_WRITE|KEY_WOW64_64KEY, NULL, &key_render, NULL);
    RegCloseKey(root);
    cur = key_capture;
    curflow = eCapture;
    if (ret != ERROR_SUCCESS)
    {
        RegCloseKey(key_capture);
        key_render = key_capture = NULL;
        WARN("Couldn't create key: %u\n", ret);
        return E_FAIL;
    }

    do {
        WCHAR guidvalue[39];
        GUID guid;
        DWORD len;
        PROPVARIANT pv = { VT_EMPTY };

        len = ARRAY_SIZE(guidvalue);
        ret = RegEnumKeyExW(cur, i++, guidvalue, &len, NULL, NULL, NULL, NULL);
        if (ret == ERROR_NO_MORE_ITEMS)
        {
            if (cur == key_capture)
            {
                cur = key_render;
                curflow = eRender;
                i = 0;
                continue;
            }
            break;
        }
        if (ret != ERROR_SUCCESS)
            continue;
        if (SUCCEEDED(CLSIDFromString(guidvalue, &guid))
            && SUCCEEDED(MMDevice_GetPropValue(&guid, curflow, (const PROPERTYKEY*)&DEVPKEY_Device_FriendlyName, &pv))
            && pv.vt == VT_LPWSTR)
        {
            DWORD size_bytes = (lstrlenW(pv.u.pwszVal) + 1) * sizeof(WCHAR);
            WCHAR *name = HeapAlloc(GetProcessHeap(), 0, size_bytes);
            memcpy(name, pv.u.pwszVal, size_bytes);
            MMDevice_Create(name, &guid, curflow,
                    DEVICE_STATE_NOTPRESENT, FALSE);
            CoTaskMemFree(pv.u.pwszVal);
        }
    } while (1);

    return S_OK;
}