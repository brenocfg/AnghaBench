#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* location; } ;
struct TYPE_7__ {int /*<<< orphan*/  IHTMLLocation_iface; } ;
typedef  TYPE_1__ HTMLLocation ;
typedef  TYPE_2__ HTMLInnerWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLLocation_Create (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  IHTMLLocation_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT get_location(HTMLInnerWindow *This, HTMLLocation **ret)
{
    if(This->location) {
        IHTMLLocation_AddRef(&This->location->IHTMLLocation_iface);
    }else {
        HRESULT hres;

        hres = HTMLLocation_Create(This, &This->location);
        if(FAILED(hres))
            return hres;
    }

    *ret = This->location;
    return S_OK;
}