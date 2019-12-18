#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  IConnectionPointContainer_iface; } ;
struct TYPE_7__ {int /*<<< orphan*/  IProvideClassInfo_iface; int /*<<< orphan*/  IObjectSafety_iface; int /*<<< orphan*/  IOleContainer_iface; int /*<<< orphan*/  IObjectWithSite_iface; int /*<<< orphan*/  IPersistHistory_iface; int /*<<< orphan*/  ISupportErrorInfo_iface; int /*<<< orphan*/  IHTMLDocument2_iface; int /*<<< orphan*/  IPersistStreamInit_iface; TYPE_1__ cp_container; int /*<<< orphan*/  IHlinkTarget_iface; int /*<<< orphan*/  IOleControl_iface; int /*<<< orphan*/  IOleCommandTarget_iface; int /*<<< orphan*/  IServiceProvider_iface; int /*<<< orphan*/  IOleInPlaceObjectWindowless_iface; int /*<<< orphan*/  IOleInPlaceActiveObject_iface; int /*<<< orphan*/  IViewObjectEx_iface; int /*<<< orphan*/  IOleDocumentView_iface; int /*<<< orphan*/  IOleDocument_iface; int /*<<< orphan*/  IOleObject_iface; int /*<<< orphan*/  IMonikerProp_iface; int /*<<< orphan*/  IPersistFile_iface; int /*<<< orphan*/  IPersistMoniker_iface; int /*<<< orphan*/  IHTMLDocument7_iface; int /*<<< orphan*/  IHTMLDocument6_iface; int /*<<< orphan*/  IHTMLDocument5_iface; int /*<<< orphan*/  IHTMLDocument4_iface; int /*<<< orphan*/  IHTMLDocument3_iface; int /*<<< orphan*/  IDispatchEx_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ HTMLDocument ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_CMarkup ; 
 int /*<<< orphan*/  DIID_DispHTMLDocument ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,TYPE_2__*,void**) ; 
 int /*<<< orphan*/  IID_IConnectionPointContainer ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_IExternalConnection ; 
 int /*<<< orphan*/  IID_IHTMLDocument ; 
 int /*<<< orphan*/  IID_IHTMLDocument2 ; 
 int /*<<< orphan*/  IID_IHTMLDocument3 ; 
 int /*<<< orphan*/  IID_IHTMLDocument4 ; 
 int /*<<< orphan*/  IID_IHTMLDocument5 ; 
 int /*<<< orphan*/  IID_IHTMLDocument6 ; 
 int /*<<< orphan*/  IID_IHTMLDocument7 ; 
 int /*<<< orphan*/  IID_IHlinkTarget ; 
 int /*<<< orphan*/  IID_IMarshal ; 
 int /*<<< orphan*/  IID_IMonikerProp ; 
 int /*<<< orphan*/  IID_IObjectSafety ; 
 int /*<<< orphan*/  IID_IObjectWithSite ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 int /*<<< orphan*/  IID_IOleContainer ; 
 int /*<<< orphan*/  IID_IOleControl ; 
 int /*<<< orphan*/  IID_IOleDocument ; 
 int /*<<< orphan*/  IID_IOleDocumentView ; 
 int /*<<< orphan*/  IID_IOleInPlaceActiveObject ; 
 int /*<<< orphan*/  IID_IOleInPlaceObject ; 
 int /*<<< orphan*/  IID_IOleInPlaceObjectWindowless ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IID_IOleWindow ; 
 int /*<<< orphan*/  IID_IPersist ; 
 int /*<<< orphan*/  IID_IPersistFile ; 
 int /*<<< orphan*/  IID_IPersistHistory ; 
 int /*<<< orphan*/  IID_IPersistMoniker ; 
 int /*<<< orphan*/  IID_IPersistPropertyBag ; 
 int /*<<< orphan*/  IID_IPersistStreamInit ; 
 int /*<<< orphan*/  IID_IProvideClassInfo ; 
 int /*<<< orphan*/  IID_IRunnableObject ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IID_IStdMarshalInfo ; 
 int /*<<< orphan*/  IID_ISupportErrorInfo ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IID_IViewObject ; 
 int /*<<< orphan*/  IID_IViewObject2 ; 
 int /*<<< orphan*/  IID_IViewObjectEx ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,void**) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL htmldoc_qi(HTMLDocument *This, REFIID riid, void **ppv)
{
    *ppv = NULL;

    if(IsEqualGUID(&IID_IUnknown, riid))
        *ppv = &This->IHTMLDocument2_iface;
    else if(IsEqualGUID(&IID_IDispatch, riid))
        *ppv = &This->IDispatchEx_iface;
    else if(IsEqualGUID(&IID_IDispatchEx, riid))
        *ppv = &This->IDispatchEx_iface;
    else if(IsEqualGUID(&IID_IHTMLDocument, riid))
        *ppv = &This->IHTMLDocument2_iface;
    else if(IsEqualGUID(&IID_IHTMLDocument2, riid))
        *ppv = &This->IHTMLDocument2_iface;
    else if(IsEqualGUID(&IID_IHTMLDocument3, riid))
        *ppv = &This->IHTMLDocument3_iface;
    else if(IsEqualGUID(&IID_IHTMLDocument4, riid))
        *ppv = &This->IHTMLDocument4_iface;
    else if(IsEqualGUID(&IID_IHTMLDocument5, riid))
        *ppv = &This->IHTMLDocument5_iface;
    else if(IsEqualGUID(&IID_IHTMLDocument6, riid))
        *ppv = &This->IHTMLDocument6_iface;
    else if(IsEqualGUID(&IID_IHTMLDocument7, riid))
        *ppv = &This->IHTMLDocument7_iface;
    else if(IsEqualGUID(&IID_IPersist, riid))
        *ppv = &This->IPersistFile_iface;
    else if(IsEqualGUID(&IID_IPersistMoniker, riid))
        *ppv = &This->IPersistMoniker_iface;
    else if(IsEqualGUID(&IID_IPersistFile, riid))
        *ppv = &This->IPersistFile_iface;
    else if(IsEqualGUID(&IID_IMonikerProp, riid))
        *ppv = &This->IMonikerProp_iface;
    else if(IsEqualGUID(&IID_IOleObject, riid))
        *ppv = &This->IOleObject_iface;
    else if(IsEqualGUID(&IID_IOleDocument, riid))
        *ppv = &This->IOleDocument_iface;
    else if(IsEqualGUID(&IID_IOleDocumentView, riid))
        *ppv = &This->IOleDocumentView_iface;
    else if(IsEqualGUID(&IID_IOleInPlaceActiveObject, riid))
        *ppv = &This->IOleInPlaceActiveObject_iface;
    else if(IsEqualGUID(&IID_IViewObject, riid))
        *ppv = &This->IViewObjectEx_iface;
    else if(IsEqualGUID(&IID_IViewObject2, riid))
        *ppv = &This->IViewObjectEx_iface;
    else if(IsEqualGUID(&IID_IViewObjectEx, riid))
        *ppv = &This->IViewObjectEx_iface;
    else if(IsEqualGUID(&IID_IOleWindow, riid))
        *ppv = &This->IOleInPlaceActiveObject_iface;
    else if(IsEqualGUID(&IID_IOleInPlaceObject, riid))
        *ppv = &This->IOleInPlaceObjectWindowless_iface;
    else if(IsEqualGUID(&IID_IOleInPlaceObjectWindowless, riid))
        *ppv = &This->IOleInPlaceObjectWindowless_iface;
    else if(IsEqualGUID(&IID_IServiceProvider, riid))
        *ppv = &This->IServiceProvider_iface;
    else if(IsEqualGUID(&IID_IOleCommandTarget, riid))
        *ppv = &This->IOleCommandTarget_iface;
    else if(IsEqualGUID(&IID_IOleControl, riid))
        *ppv = &This->IOleControl_iface;
    else if(IsEqualGUID(&IID_IHlinkTarget, riid))
        *ppv = &This->IHlinkTarget_iface;
    else if(IsEqualGUID(&IID_IConnectionPointContainer, riid))
        *ppv = &This->cp_container.IConnectionPointContainer_iface;
    else if(IsEqualGUID(&IID_IPersistStreamInit, riid))
        *ppv = &This->IPersistStreamInit_iface;
    else if(IsEqualGUID(&DIID_DispHTMLDocument, riid))
        *ppv = &This->IHTMLDocument2_iface;
    else if(IsEqualGUID(&IID_ISupportErrorInfo, riid))
        *ppv = &This->ISupportErrorInfo_iface;
    else if(IsEqualGUID(&IID_IPersistHistory, riid))
        *ppv = &This->IPersistHistory_iface;
    else if(IsEqualGUID(&IID_IObjectWithSite, riid))
        *ppv = &This->IObjectWithSite_iface;
    else if(IsEqualGUID(&IID_IOleContainer, riid))
        *ppv = &This->IOleContainer_iface;
    else if(IsEqualGUID(&IID_IObjectSafety, riid))
        *ppv = &This->IObjectSafety_iface;
    else if(IsEqualGUID(&IID_IProvideClassInfo, riid))
        *ppv = &This->IProvideClassInfo_iface;
    else if(IsEqualGUID(&CLSID_CMarkup, riid)) {
        FIXME("(%p)->(CLSID_CMarkup %p)\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IRunnableObject, riid)) {
        TRACE("(%p)->(IID_IRunnableObject %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IPersistPropertyBag, riid)) {
        TRACE("(%p)->(IID_IPersistPropertyBag %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IMarshal, riid)) {
        TRACE("(%p)->(IID_IMarshal %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IExternalConnection, riid)) {
        TRACE("(%p)->(IID_IExternalConnection %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else if(IsEqualGUID(&IID_IStdMarshalInfo, riid)) {
        TRACE("(%p)->(IID_IStdMarshalInfo %p) returning NULL\n", This, ppv);
        *ppv = NULL;
    }else {
        return FALSE;
    }

    if(*ppv)
        IUnknown_AddRef((IUnknown*)*ppv);
    return TRUE;
}