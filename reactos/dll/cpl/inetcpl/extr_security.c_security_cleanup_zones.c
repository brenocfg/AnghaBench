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
struct TYPE_3__ {scalar_t__ sec_mgr; scalar_t__ zone_mgr; scalar_t__ zone_enumerator; } ;
typedef  TYPE_1__ secdlg_data ;

/* Variables and functions */
 int /*<<< orphan*/  IInternetSecurityManager_Release (scalar_t__) ; 
 int /*<<< orphan*/  IInternetZoneManager_DestroyZoneEnumerator (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IInternetZoneManager_Release (scalar_t__) ; 

__attribute__((used)) static void security_cleanup_zones(secdlg_data *sd)
{
    if (sd->zone_enumerator) {
        IInternetZoneManager_DestroyZoneEnumerator(sd->zone_mgr, sd->zone_enumerator);
    }

    if (sd->zone_mgr) {
        IInternetZoneManager_Release(sd->zone_mgr);
    }

    if (sd->sec_mgr) {
        IInternetSecurityManager_Release(sd->sec_mgr);
    }
}