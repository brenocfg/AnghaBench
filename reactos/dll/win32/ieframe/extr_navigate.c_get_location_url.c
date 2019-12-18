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
struct TYPE_3__ {scalar_t__ url; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DocHost ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (scalar_t__) ; 
 int /*<<< orphan*/  SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT get_location_url(DocHost *This, BSTR *ret)
{
    FIXME("semi-stub\n");

    *ret = This->url ? SysAllocString(This->url) : SysAllocStringLen(NULL, 0);
    if(!*ret)
        return E_OUTOFMEMORY;

    return This->url ? S_OK : S_FALSE;
}