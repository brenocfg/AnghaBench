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
typedef  int /*<<< orphan*/  BSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
#define  VT_BSTR 131 
#define  VT_I4 130 
#define  VT_R4 129 
#define  VT_R8 128 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  V_R4 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  V_R8 (int /*<<< orphan*/  const*) ; 
 int V_VT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VarBstrFromI4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VarBstrFromR4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VarBstrFromR8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/  const*) ; 
 scalar_t__ nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT var2str(const VARIANT *p, nsAString *nsstr)
{
    BSTR str;
    BOOL ret;
    HRESULT hres;

    switch(V_VT(p)) {
    case VT_BSTR:
        return nsAString_Init(nsstr, V_BSTR(p))?
            S_OK : E_OUTOFMEMORY;
    case VT_R8:
        hres = VarBstrFromR8(V_R8(p), 0, 0, &str);
        break;
    case VT_R4:
        hres = VarBstrFromR4(V_R4(p), 0, 0, &str);
        break;
    case VT_I4:
        hres = VarBstrFromI4(V_I4(p), 0, 0, &str);
        break;
    default:
        FIXME("unsupported arg %s\n", debugstr_variant(p));
        return E_NOTIMPL;
    }
    if (FAILED(hres))
        return hres;

    ret = nsAString_Init(nsstr, str);
    SysFreeString(str);
    return ret ? S_OK : E_OUTOFMEMORY;
}