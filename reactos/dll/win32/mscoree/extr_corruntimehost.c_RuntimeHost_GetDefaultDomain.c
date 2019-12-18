#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * default_domain; } ;
typedef  TYPE_1__ RuntimeHost ;
typedef  int /*<<< orphan*/  MonoDomain ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RuntimeHost_AddDomain (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT RuntimeHost_GetDefaultDomain(RuntimeHost *This, MonoDomain **result)
{
    HRESULT res=S_OK;

    EnterCriticalSection(&This->lock);

    if (This->default_domain) goto end;

    res = RuntimeHost_AddDomain(This, &This->default_domain);

end:
    *result = This->default_domain;

    LeaveCriticalSection(&This->lock);

    return res;
}