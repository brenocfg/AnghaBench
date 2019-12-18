#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  property_set_storage; int /*<<< orphan*/  currentFile; int /*<<< orphan*/  url; int /*<<< orphan*/  refCount; } ;
typedef  TYPE_1__ InternetShortcut ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPropertySetStorage_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_module () ; 

__attribute__((used)) static ULONG Unknown_Release(InternetShortcut *This)
{
    ULONG count;
    TRACE("(%p)\n", This);
    count = InterlockedDecrement(&This->refCount);
    if (count == 0)
    {
        CoTaskMemFree(This->url);
        CoTaskMemFree(This->currentFile);
        IPropertySetStorage_Release(This->property_set_storage);
        heap_free(This);
        unlock_module();
    }
    return count;
}