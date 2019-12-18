#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t styleid_t ;
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMCSSStyleDeclaration ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  const* name; } ;
typedef  int /*<<< orphan*/  const* LPWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int ATTR_FIX_PX ; 
 int ATTR_FIX_URL ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  const* emptyW ; 
 int /*<<< orphan*/ * fix_px_value (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * fix_url_value (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIDOMCSSStyleDeclaration_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* style_tbl ; 

HRESULT set_nsstyle_attr(nsIDOMCSSStyleDeclaration *nsstyle, styleid_t sid, const WCHAR *value, DWORD flags)
{
    nsAString str_name, str_value, str_empty;
    LPWSTR val = NULL;
    nsresult nsres;

    if(value) {
        if(flags & ATTR_FIX_PX)
            val = fix_px_value(value);
        else if(flags & ATTR_FIX_URL)
            val = fix_url_value(value);
    }

    nsAString_InitDepend(&str_name, style_tbl[sid].name);
    nsAString_InitDepend(&str_value, val ? val : value);
    nsAString_InitDepend(&str_empty, emptyW);

    nsres = nsIDOMCSSStyleDeclaration_SetProperty(nsstyle, &str_name, &str_value, &str_empty);
    if(NS_FAILED(nsres))
        ERR("SetProperty failed: %08x\n", nsres);

    nsAString_Finish(&str_name);
    nsAString_Finish(&str_value);
    nsAString_Finish(&str_empty);
    heap_free(val);

    return S_OK;
}