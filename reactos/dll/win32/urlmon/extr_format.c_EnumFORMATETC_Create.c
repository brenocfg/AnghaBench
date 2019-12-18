#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; int it; int fetc_cnt; TYPE_1__ IEnumFORMATETC_iface; void* fetc; } ;
typedef  TYPE_1__ IEnumFORMATETC ;
typedef  int /*<<< orphan*/  FORMATETC ;
typedef  TYPE_2__ EnumFORMATETC ;

/* Variables and functions */
 int /*<<< orphan*/  EnumFORMATETCVtbl ; 
 int /*<<< orphan*/  URLMON_LockModule () ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static IEnumFORMATETC *EnumFORMATETC_Create(UINT cfmtetc, const FORMATETC *rgfmtetc, UINT it)
{
    EnumFORMATETC *ret = heap_alloc(sizeof(EnumFORMATETC));

    URLMON_LockModule();

    ret->IEnumFORMATETC_iface.lpVtbl = &EnumFORMATETCVtbl;
    ret->ref = 1;
    ret->it = it;
    ret->fetc_cnt = cfmtetc;

    ret->fetc = heap_alloc(cfmtetc*sizeof(FORMATETC));
    memcpy(ret->fetc, rgfmtetc, cfmtetc*sizeof(FORMATETC));

    return &ret->IEnumFORMATETC_iface;
}