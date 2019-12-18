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
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
#define  VT_BSTR 131 
#define  VT_EMPTY 130 
#define  VT_ERROR 129 
#define  VT_NULL 128 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT variant_to_nsastr(VARIANT var, nsAString *ret)
{
    switch(V_VT(&var)) {
        case VT_NULL:
        case VT_ERROR:
        case VT_EMPTY:
            nsAString_Init(ret, NULL);
            return S_OK;
        case VT_BSTR:
            nsAString_InitDepend(ret, V_BSTR(&var));
            return S_OK;
        default:
            FIXME("Unsupported VARIANT: %s\n", debugstr_variant(&var));
            return E_INVALIDARG;
    }
}