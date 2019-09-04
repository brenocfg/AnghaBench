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
struct TYPE_3__ {int ref; int /*<<< orphan*/  riidInst; int /*<<< orphan*/  lpfnCI; int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  scalar_t__ PLONG ;
typedef  int /*<<< orphan*/  LPFNCREATEINSTANCE ;
typedef  int /*<<< orphan*/ * LPCLASSFACTORY ;
typedef  TYPE_1__ IClassFactoryImpl ;
typedef  int /*<<< orphan*/  IClassFactory ;

/* Variables and functions */
 TYPE_1__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  InterlockedIncrement (scalar_t__) ; 
 int /*<<< orphan*/  dclfvt ; 

IClassFactory * 
IClassFactory_fnConstructor(
    LPFNCREATEINSTANCE lpfnCI, 
    PLONG pcRefDll, 
    REFIID riidInst)
{
    IClassFactoryImpl* lpclf;

    lpclf = CoTaskMemAlloc(sizeof(IClassFactoryImpl));
    lpclf->ref = 1;
    lpclf->lpVtbl = &dclfvt;
    lpclf->lpfnCI = lpfnCI;

    if (pcRefDll)
        InterlockedIncrement(pcRefDll);
    lpclf->riidInst = riidInst;

    return (LPCLASSFACTORY)lpclf;
}