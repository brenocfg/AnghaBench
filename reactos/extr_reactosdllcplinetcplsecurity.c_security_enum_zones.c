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
struct TYPE_3__ {int /*<<< orphan*/  num_zones; int /*<<< orphan*/  zone_enumerator; int /*<<< orphan*/  zone_mgr; int /*<<< orphan*/  sec_mgr; } ;
typedef  TYPE_1__ secdlg_data ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoInternetCreateSecurityManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoInternetCreateZoneManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetZoneManager_CreateZoneEnumerator (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT security_enum_zones(secdlg_data * sd)
{
    HRESULT hr;

    hr = CoInternetCreateSecurityManager(NULL, &sd->sec_mgr, 0);
    if (SUCCEEDED(hr)) {
        hr = CoInternetCreateZoneManager(NULL, &sd->zone_mgr, 0);
        if (SUCCEEDED(hr)) {
            hr = IInternetZoneManager_CreateZoneEnumerator(sd->zone_mgr, &sd->zone_enumerator, &sd->num_zones, 0);
        }
    }
    return hr;
}