#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int readed; int bom; int /*<<< orphan*/  IBindStatusCallback_iface; } ;
struct TYPE_12__ {int /*<<< orphan*/  doc; } ;
struct TYPE_11__ {int /*<<< orphan*/  IHTMLScriptElement_iface; } ;
struct TYPE_10__ {TYPE_5__ bsc; int /*<<< orphan*/  buf; void* hres; TYPE_2__* script_elem; int /*<<< orphan*/  scheme; } ;
typedef  TYPE_1__ ScriptBSC ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  TYPE_2__ HTMLScriptElement ;
typedef  TYPE_3__ HTMLInnerWindow ;
typedef  void* HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
#define  BOM_UTF16 129 
#define  BOM_UTF8 128 
 int /*<<< orphan*/  CP_UTF8 ; 
 void* CreateURLMonikerEx2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 void* E_FAIL ; 
 void* E_OUTOFMEMORY ; 
 scalar_t__ FAILED (void*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLScriptElement_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 void* IUri_GetScheme (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ SUCCEEDED (void*) ; 
 void* S_OK ; 
 int /*<<< orphan*/  ScriptBSCVtbl ; 
 int /*<<< orphan*/  URL_MK_UNIFORM ; 
 int /*<<< orphan*/  URL_SCHEME_UNKNOWN ; 
 int /*<<< orphan*/  get_document_charset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_bscallback (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* start_binding (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT bind_script_to_text(HTMLInnerWindow *window, IUri *uri, HTMLScriptElement *script_elem, WCHAR **ret)
{
    UINT cp = CP_UTF8;
    ScriptBSC *bsc;
    IMoniker *mon;
    WCHAR *text;
    HRESULT hres;

    hres = CreateURLMonikerEx2(NULL, uri, &mon, URL_MK_UNIFORM);
    if(FAILED(hres))
        return hres;

    bsc = heap_alloc_zero(sizeof(*bsc));
    if(!bsc) {
        IMoniker_Release(mon);
        return E_OUTOFMEMORY;
    }

    init_bscallback(&bsc->bsc, &ScriptBSCVtbl, mon, 0);
    IMoniker_Release(mon);
    bsc->hres = E_FAIL;

    hres = IUri_GetScheme(uri, &bsc->scheme);
    if(FAILED(hres))
        bsc->scheme = URL_SCHEME_UNKNOWN;

    IHTMLScriptElement_AddRef(&script_elem->IHTMLScriptElement_iface);
    bsc->script_elem = script_elem;

    hres = start_binding(window, &bsc->bsc, NULL);
    if(SUCCEEDED(hres))
        hres = bsc->hres;
    if(FAILED(hres)) {
        IBindStatusCallback_Release(&bsc->bsc.IBindStatusCallback_iface);
        return hres;
    }

    if(!bsc->bsc.readed) {
        *ret = NULL;
        return S_OK;
    }

    switch(bsc->bsc.bom) {
    case BOM_UTF16:
        if(bsc->bsc.readed % sizeof(WCHAR)) {
            FIXME("The buffer is not a valid utf16 string\n");
            hres = E_FAIL;
            break;
        }

        text = heap_alloc(bsc->bsc.readed+sizeof(WCHAR));
        if(!text) {
            hres = E_OUTOFMEMORY;
            break;
        }

        memcpy(text, bsc->buf, bsc->bsc.readed);
        text[bsc->bsc.readed/sizeof(WCHAR)] = 0;
        break;

    default:
        /* FIXME: Try to use charset from HTTP headers first */
        cp = get_document_charset(window->doc);
        /* fall through */
    case BOM_UTF8: {
        DWORD len;

        len = MultiByteToWideChar(cp, 0, bsc->buf, bsc->bsc.readed, NULL, 0);
        text = heap_alloc((len+1)*sizeof(WCHAR));
        if(!text) {
            hres = E_OUTOFMEMORY;
            break;
        }

        MultiByteToWideChar(cp, 0, bsc->buf, bsc->bsc.readed, text, len);
        text[len] = 0;
    }
    }

    IBindStatusCallback_Release(&bsc->bsc.IBindStatusCallback_iface);
    if(FAILED(hres))
        return hres;

    *ret = text;
    return S_OK;
}