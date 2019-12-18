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
typedef  int /*<<< orphan*/  STDMETHODIMP ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IDropTarget ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IDropTarget_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDropTarget ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static STDMETHODIMP DropTarget_QueryInterface(IDropTarget *self, REFIID riid,
                                              void **ppvObject)
{
    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IDropTarget)) {
        *ppvObject = self;
        IDropTarget_AddRef(self);
        return S_OK;
    }

    *ppvObject = NULL;
    return E_NOINTERFACE;
}