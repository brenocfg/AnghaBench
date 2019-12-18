#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_3__ {unsigned int elem_vars_cnt; unsigned int elem_vars_size; int /*<<< orphan*/ ** elem_vars; int /*<<< orphan*/  nsdoc; } ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ MSHTML_DISPID_CUSTOM_MIN ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ ** heap_alloc (int) ; 
 int /*<<< orphan*/ ** heap_realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_GetElementsByName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNodeList_GetLength (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT dispid_from_elem_name(HTMLDocumentNode *This, BSTR name, DISPID *dispid)
{
    nsIDOMNodeList *node_list;
    nsAString name_str;
    UINT32 len;
    unsigned i;
    nsresult nsres;

    if(!This->nsdoc)
        return DISP_E_UNKNOWNNAME;

    nsAString_InitDepend(&name_str, name);
    nsres = nsIDOMHTMLDocument_GetElementsByName(This->nsdoc, &name_str, &node_list);
    nsAString_Finish(&name_str);
    if(NS_FAILED(nsres))
        return E_FAIL;

    nsres = nsIDOMNodeList_GetLength(node_list, &len);
    nsIDOMNodeList_Release(node_list);
    if(NS_FAILED(nsres))
        return E_FAIL;

    if(!len)
        return DISP_E_UNKNOWNNAME;

    for(i=0; i < This->elem_vars_cnt; i++) {
        if(!strcmpW(name, This->elem_vars[i])) {
            *dispid = MSHTML_DISPID_CUSTOM_MIN+i;
            return S_OK;
        }
    }

    if(This->elem_vars_cnt == This->elem_vars_size) {
        WCHAR **new_vars;

        if(This->elem_vars_size) {
            new_vars = heap_realloc(This->elem_vars, This->elem_vars_size*2*sizeof(WCHAR*));
            if(!new_vars)
                return E_OUTOFMEMORY;
            This->elem_vars_size *= 2;
        }else {
            new_vars = heap_alloc(16*sizeof(WCHAR*));
            if(!new_vars)
                return E_OUTOFMEMORY;
            This->elem_vars_size = 16;
        }

        This->elem_vars = new_vars;
    }

    This->elem_vars[This->elem_vars_cnt] = heap_strdupW(name);
    if(!This->elem_vars[This->elem_vars_cnt])
        return E_OUTOFMEMORY;

    *dispid = MSHTML_DISPID_CUSTOM_MIN+This->elem_vars_cnt++;
    return S_OK;
}