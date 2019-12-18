#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT16 ;
struct TYPE_4__ {int /*<<< orphan*/  nsdoc; } ;
typedef  int /*<<< orphan*/  HTMLElement ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int DOCUMENT_POSITION_CONTAINS ; 
 int DOCUMENT_POSITION_PRECEDING ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  IID_nsIDOMElement ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_elem (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIDOMElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMHTMLDocument_GetElementById (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nsIDOMHTMLDocument_GetElementsByName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nsIDOMNodeList_Item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMNode_CompareDocumentPosition (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 

HRESULT get_doc_elem_by_id(HTMLDocumentNode *doc, const WCHAR *id, HTMLElement **ret)
{
    nsIDOMNodeList *nsnode_list;
    nsIDOMElement *nselem;
    nsIDOMNode *nsnode;
    nsAString id_str;
    nsresult nsres;
    HRESULT hres;

    if(!doc->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsAString_InitDepend(&id_str, id);
    /* get element by id attribute */
    nsres = nsIDOMHTMLDocument_GetElementById(doc->nsdoc, &id_str, &nselem);
    if(FAILED(nsres)) {
        ERR("GetElementById failed: %08x\n", nsres);
        nsAString_Finish(&id_str);
        return E_FAIL;
    }

    /* get first element by name attribute */
    nsres = nsIDOMHTMLDocument_GetElementsByName(doc->nsdoc, &id_str, &nsnode_list);
    nsAString_Finish(&id_str);
    if(FAILED(nsres)) {
        ERR("getElementsByName failed: %08x\n", nsres);
        if(nselem)
            nsIDOMElement_Release(nselem);
        return E_FAIL;
    }

    nsres = nsIDOMNodeList_Item(nsnode_list, 0, &nsnode);
    nsIDOMNodeList_Release(nsnode_list);
    assert(nsres == NS_OK);

    if(nsnode && nselem) {
        UINT16 pos;

        nsres = nsIDOMNode_CompareDocumentPosition(nsnode, (nsIDOMNode*)nselem, &pos);
        if(NS_FAILED(nsres)) {
            FIXME("CompareDocumentPosition failed: 0x%08x\n", nsres);
            nsIDOMNode_Release(nsnode);
            nsIDOMElement_Release(nselem);
            return E_FAIL;
        }

        TRACE("CompareDocumentPosition gave: 0x%x\n", pos);
        if(!(pos & (DOCUMENT_POSITION_PRECEDING | DOCUMENT_POSITION_CONTAINS))) {
            nsIDOMElement_Release(nselem);
            nselem = NULL;
        }
    }

    if(nsnode) {
        if(!nselem) {
            nsres = nsIDOMNode_QueryInterface(nsnode, &IID_nsIDOMElement, (void**)&nselem);
            assert(nsres == NS_OK);
        }
        nsIDOMNode_Release(nsnode);
    }

    if(!nselem) {
        *ret = NULL;
        return S_OK;
    }

    hres = get_elem(doc, nselem, ret);
    nsIDOMElement_Release(nselem);
    return hres;
}