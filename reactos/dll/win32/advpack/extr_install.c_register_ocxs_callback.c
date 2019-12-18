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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HMODULE ;
typedef  int /*<<< orphan*/  HINF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  LOAD_WITH_ALTERED_SEARCH_PATH ; 
 scalar_t__ LoadLibraryExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_INF_STRING_LENGTH ; 
 scalar_t__ S_OK ; 
 scalar_t__ SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ do_ocx_reg (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT register_ocxs_callback(HINF hinf, PCWSTR field, const void *arg)
{
    HMODULE hm;
    INFCONTEXT context;
    HRESULT hr = S_OK;

    BOOL ok = SetupFindFirstLineW(hinf, field, NULL, &context);
    
    for (; ok; ok = SetupFindNextLine(&context, &context))
    {
        WCHAR buffer[MAX_INF_STRING_LENGTH];

        /* get OCX filename */
        if (!SetupGetStringFieldW(&context, 1, buffer, ARRAY_SIZE(buffer), NULL))
            continue;

        hm = LoadLibraryExW(buffer, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (hm)
        {
            if (do_ocx_reg(hm, TRUE, NULL, NULL) != S_OK)
                hr = E_FAIL;

            FreeLibrary(hm);
        }
        else
            hr = E_FAIL;

        if (FAILED(hr))
        {
            /* FIXME: display a message box */
            break;
        }
    }

    return hr;
}