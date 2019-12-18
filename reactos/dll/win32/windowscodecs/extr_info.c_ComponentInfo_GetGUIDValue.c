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
typedef  int /*<<< orphan*/  guid_string ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int RRF_NOEXPAND ; 
 int RRF_RT_REG_SZ ; 
 scalar_t__ RegGetValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static HRESULT ComponentInfo_GetGUIDValue(HKEY classkey, LPCWSTR value,
    GUID *result)
{
    LONG ret;
    WCHAR guid_string[39];
    DWORD cbdata = sizeof(guid_string);
    HRESULT hr;

    if (!result)
        return E_INVALIDARG;

    ret = RegGetValueW(classkey, NULL, value, RRF_RT_REG_SZ|RRF_NOEXPAND, NULL,
        guid_string, &cbdata);

    if (ret != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(ret);

    if (cbdata < sizeof(guid_string))
    {
        ERR("incomplete GUID value\n");
        return E_FAIL;
    }

    hr = CLSIDFromString(guid_string, result);

    return hr;
}