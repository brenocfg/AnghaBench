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
struct TYPE_3__ {int /*<<< orphan*/  hStoreProv; int /*<<< orphan*/  (* provControl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ;} ;
typedef  TYPE_1__ WINE_PROVIDERSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static BOOL ProvStore_control(WINECRYPT_CERTSTORE *cert_store, DWORD dwFlags, DWORD dwCtrlType, void const *pvCtrlPara)
{
    WINE_PROVIDERSTORE *store = (WINE_PROVIDERSTORE*)cert_store;
    BOOL ret = TRUE;

    TRACE("(%p, %08x, %d, %p)\n", store, dwFlags, dwCtrlType,
     pvCtrlPara);

    if (store->provControl)
        ret = store->provControl(store->hStoreProv, dwFlags, dwCtrlType,
         pvCtrlPara);
    return ret;
}