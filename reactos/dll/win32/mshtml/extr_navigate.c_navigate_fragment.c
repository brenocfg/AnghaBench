#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  selector_formatW ;
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMLocation ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsIDOMElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  char WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  IHTMLWindow2_iface; TYPE_2__* inner_window; } ;
struct TYPE_12__ {TYPE_4__ base; TYPE_3__* doc_obj; int /*<<< orphan*/  nswindow; } ;
struct TYPE_10__ {scalar_t__ doc_object_service; } ;
struct TYPE_9__ {TYPE_1__* doc; } ;
struct TYPE_8__ {int /*<<< orphan*/  nsdoc; } ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_5__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDocObjectService_FireDocumentComplete (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDocObjectService_FireNavigateComplete2 (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLElement ; 
 int /*<<< orphan*/  IUri_GetFragment (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (char*) ; 
 int SysStringLen (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nsIDOMElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_QuerySelector (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_ScrollIntoView (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsIDOMLocation_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMLocation_SetHash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMWindow_GetLocation (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_current_uri (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char*) ; 

__attribute__((used)) static HRESULT navigate_fragment(HTMLOuterWindow *window, IUri *uri)
{
    nsIDOMLocation *nslocation;
    nsAString nsfrag_str;
    WCHAR *selector;
    BSTR frag;
    nsresult nsres;
    HRESULT hres;

    const WCHAR selector_formatW[] = {'a','[','i','d','=','"','%','s','"',']',0};

    set_current_uri(window, uri);

    nsres = nsIDOMWindow_GetLocation(window->nswindow, &nslocation);
    if(FAILED(nsres) || !nslocation)
        return E_FAIL;

    hres = IUri_GetFragment(uri, &frag);
    if(FAILED(hres)) {
        nsIDOMLocation_Release(nslocation);
        return hres;
    }

    nsAString_InitDepend(&nsfrag_str, frag);
    nsres = nsIDOMLocation_SetHash(nslocation, &nsfrag_str);
    nsAString_Finish(&nsfrag_str);
    nsIDOMLocation_Release(nslocation);
    if(NS_FAILED(nsres))
        ERR("SetHash failed: %08x\n", nsres);

    /*
     * IE supports scrolling to anchor elements with "#hash" ids (note that '#' is part of the id),
     * while Gecko scrolls only to elements with "hash" ids. We scroll the page ourselves if
     * a[id="#hash"] element can be found.
     */
    selector = heap_alloc(sizeof(selector_formatW)+SysStringLen(frag)*sizeof(WCHAR));
    if(selector) {
        nsIDOMElement *nselem = NULL;
        nsAString selector_str;

        sprintfW(selector, selector_formatW, frag);
        nsAString_InitDepend(&selector_str, selector);
        /* NOTE: Gecko doesn't set result to NULL if there is no match, so nselem must be initialized */
        nsres = nsIDOMHTMLDocument_QuerySelector(window->base.inner_window->doc->nsdoc, &selector_str, &nselem);
        nsAString_Finish(&selector_str);
        heap_free(selector);
        if(NS_SUCCEEDED(nsres) && nselem) {
            nsIDOMHTMLElement *html_elem;

            nsres = nsIDOMElement_QueryInterface(nselem, &IID_nsIDOMHTMLElement, (void**)&html_elem);
            nsIDOMElement_Release(nselem);
            if(NS_SUCCEEDED(nsres)) {
                nsIDOMHTMLElement_ScrollIntoView(html_elem, TRUE, 1);
                nsIDOMHTMLElement_Release(html_elem);
            }
        }
    }

    SysFreeString(frag);

    if(window->doc_obj->doc_object_service) {
        IDocObjectService_FireNavigateComplete2(window->doc_obj->doc_object_service, &window->base.IHTMLWindow2_iface, 0x10);
        IDocObjectService_FireDocumentComplete(window->doc_obj->doc_object_service, &window->base.IHTMLWindow2_iface, 0);

    }

    return S_OK;
}