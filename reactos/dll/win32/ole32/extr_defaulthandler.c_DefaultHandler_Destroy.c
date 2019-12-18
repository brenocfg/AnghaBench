#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ref; int /*<<< orphan*/ * pCFObject; int /*<<< orphan*/ * storage; int /*<<< orphan*/ * dataAdviseHolder; int /*<<< orphan*/ * oleAdviseHolder; int /*<<< orphan*/ * clientSite; int /*<<< orphan*/ * dataCache; int /*<<< orphan*/ * dataCache_PersistStg; int /*<<< orphan*/  outerUnknown; struct TYPE_6__* containerObj; struct TYPE_6__* containerApp; } ;
typedef  TYPE_1__ DefaultHandler ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultHandler_Stop (TYPE_1__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDataAdviseHolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleAdviseHolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleClientSite_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static void DefaultHandler_Destroy(
  DefaultHandler* This)
{
  TRACE("(%p)\n", This);

  /* AddRef/Release may be called on this object during destruction.
   * Prevent the object being destroyed recursively by artificially raising
   * the reference count. */
  This->ref = 10000;

  /* release delegates */
  DefaultHandler_Stop(This);

  HeapFree( GetProcessHeap(), 0, This->containerApp );
  This->containerApp = NULL;
  HeapFree( GetProcessHeap(), 0, This->containerObj );
  This->containerObj = NULL;

  if (This->dataCache)
  {
    /* to balance out the release of dataCache_PersistStg which will result
     * in a reference being released from the outer unknown */
    IUnknown_AddRef(This->outerUnknown);
    IPersistStorage_Release(This->dataCache_PersistStg);
    IUnknown_Release(This->dataCache);
    This->dataCache_PersistStg = NULL;
    This->dataCache = NULL;
  }

  if (This->clientSite)
  {
    IOleClientSite_Release(This->clientSite);
    This->clientSite = NULL;
  }

  if (This->oleAdviseHolder)
  {
    IOleAdviseHolder_Release(This->oleAdviseHolder);
    This->oleAdviseHolder = NULL;
  }

  if (This->dataAdviseHolder)
  {
    IDataAdviseHolder_Release(This->dataAdviseHolder);
    This->dataAdviseHolder = NULL;
  }

  if (This->storage)
  {
    IStorage_Release(This->storage);
    This->storage = NULL;
  }

  if (This->pCFObject)
  {
    IClassFactory_Release(This->pCFObject);
    This->pCFObject = NULL;
  }

  HeapFree(GetProcessHeap(), 0, This);
}