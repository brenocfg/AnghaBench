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
struct TYPE_3__ {int /*<<< orphan*/  url; int /*<<< orphan*/  secmgr; } ;
typedef  TYPE_1__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetSecurityManager_MapUrlToZone (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int TRUE ; 
 scalar_t__ URLZONE_UNTRUSTED ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL use_gecko_script(HTMLOuterWindow *window)
{
    DWORD zone;
    HRESULT hres;

    hres = IInternetSecurityManager_MapUrlToZone(window->secmgr, window->url, &zone, 0);
    if(FAILED(hres)) {
        WARN("Could not map %s to zone: %08x\n", debugstr_w(window->url), hres);
        return TRUE;
    }

    TRACE("zone %d\n", zone);
    return zone == URLZONE_UNTRUSTED;
}