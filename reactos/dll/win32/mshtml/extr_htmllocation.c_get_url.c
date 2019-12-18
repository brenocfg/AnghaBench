#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {TYPE_2__* window; } ;
struct TYPE_8__ {TYPE_1__* outer_window; } ;
struct TYPE_7__ {TYPE_3__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/ * url; } ;
typedef  TYPE_4__ HTMLLocation ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT get_url(HTMLLocation *This, const WCHAR **ret)
{
    if(!This->window || !This->window->base.outer_window || !This->window->base.outer_window->url) {
        FIXME("No current URL\n");
        return E_NOTIMPL;
    }

    *ret = This->window->base.outer_window->url;
    return S_OK;
}