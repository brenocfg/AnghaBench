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
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct security {int refs; TYPE_1__ ISWbemSecurity_iface; int /*<<< orphan*/  authlevel; int /*<<< orphan*/  implevel; } ;
typedef  TYPE_1__ ISWbemSecurity ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 struct security* heap_alloc (int) ; 
 int /*<<< orphan*/  security_vtbl ; 
 int /*<<< orphan*/  wbemAuthenticationLevelPktPrivacy ; 
 int /*<<< orphan*/  wbemImpersonationLevelImpersonate ; 

__attribute__((used)) static HRESULT ISWbemSecurity_create( ISWbemSecurity **obj )
{
    struct security *security;

    TRACE( "%p\n", obj );

    if (!(security = heap_alloc( sizeof(*security) ))) return E_OUTOFMEMORY;
    security->ISWbemSecurity_iface.lpVtbl = &security_vtbl;
    security->refs = 1;
    security->implevel = wbemImpersonationLevelImpersonate;
    security->authlevel = wbemAuthenticationLevelPktPrivacy;

    *obj = &security->ISWbemSecurity_iface;
    TRACE( "returning iface %p\n", *obj );
    return S_OK;
}