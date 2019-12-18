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
struct TYPE_3__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  protocol; scalar_t__ urlmon; int /*<<< orphan*/  clsid; int /*<<< orphan*/ * cf; } ;
typedef  TYPE_1__ name_space ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IClassFactory_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name_space_list ; 
 int /*<<< orphan*/  session_cs ; 

HRESULT register_namespace(IClassFactory *cf, REFIID clsid, LPCWSTR protocol, BOOL urlmon_protocol)
{
    name_space *new_name_space;

    new_name_space = heap_alloc(sizeof(name_space));

    if(!urlmon_protocol)
        IClassFactory_AddRef(cf);
    new_name_space->cf = cf;
    new_name_space->clsid = *clsid;
    new_name_space->urlmon = urlmon_protocol;
    new_name_space->protocol = heap_strdupW(protocol);

    EnterCriticalSection(&session_cs);

    list_add_head(&name_space_list, &new_name_space->entry);

    LeaveCriticalSection(&session_cs);

    return S_OK;
}