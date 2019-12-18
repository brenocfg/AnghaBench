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
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  dispex_prop_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char* DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_prop_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  string_hash (char*) ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*) ; 

HRESULT jsdisp_delete_idx(jsdisp_t *obj, DWORD idx)
{
    static const WCHAR formatW[] = {'%','d',0};
    WCHAR buf[12];
    dispex_prop_t *prop;
    BOOL b;
    HRESULT hres;

    swprintf(buf, formatW, idx);

    hres = find_prop_name(obj, string_hash(buf), buf, &prop);
    if(FAILED(hres) || !prop)
        return hres;

    return delete_prop(prop, &b);
}