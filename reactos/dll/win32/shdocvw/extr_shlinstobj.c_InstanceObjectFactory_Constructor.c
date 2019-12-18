#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {TYPE_3__ IClassFactory_iface; int /*<<< orphan*/ * m_pPropertyBag; int /*<<< orphan*/  m_clsidInstance; scalar_t__ m_cRef; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/ * REFCLSID ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_1__ InstanceObjectFactory ;
typedef  int /*<<< orphan*/  IPropertyBag ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IClassFactory_AddRef (TYPE_3__*) ; 
 int /*<<< orphan*/  IClassFactory_QueryInterface (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IClassFactory_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  IPropertyBag_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstanceObjectFactory_IClassFactoryVtbl ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_alloc (int) ; 

__attribute__((used)) static HRESULT InstanceObjectFactory_Constructor(REFCLSID rclsid, IPropertyBag *pPropertyBag,
                                                 REFIID riid, LPVOID *ppvObject)
{
    InstanceObjectFactory *pInstanceObjectFactory;
    HRESULT hr = E_FAIL;

    TRACE("(RegistryPropertyBag=%p, riid=%s, ppvObject=%p)\n", pPropertyBag,
        debugstr_guid(riid), ppvObject);

    pInstanceObjectFactory = heap_alloc(sizeof(InstanceObjectFactory));
    if (pInstanceObjectFactory) {
        pInstanceObjectFactory->IClassFactory_iface.lpVtbl = &InstanceObjectFactory_IClassFactoryVtbl;
        pInstanceObjectFactory->m_cRef = 0;
        pInstanceObjectFactory->m_clsidInstance = *rclsid;
        pInstanceObjectFactory->m_pPropertyBag = pPropertyBag;
        IPropertyBag_AddRef(pPropertyBag);

        IClassFactory_AddRef(&pInstanceObjectFactory->IClassFactory_iface);
        hr = IClassFactory_QueryInterface(&pInstanceObjectFactory->IClassFactory_iface,
                                          riid, ppvObject);
        IClassFactory_Release(&pInstanceObjectFactory->IClassFactory_iface);
    }

    return hr;
}