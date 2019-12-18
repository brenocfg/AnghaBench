#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/ * url; TYPE_1__* container_vtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_url ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

HRESULT set_dochost_url(DocHost *This, const WCHAR *url)
{
    WCHAR *new_url;

    if(url) {
        new_url = heap_strdupW(url);
        if(!new_url)
            return E_OUTOFMEMORY;
    }else {
        new_url = NULL;
    }

    heap_free(This->url);
    This->url = new_url;

    This->container_vtbl->set_url(This, This->url);
    return S_OK;
}