#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ HW_VENDOR_AMD ; 
 scalar_t__ HW_VENDOR_INTEL ; 
 scalar_t__ HW_VENDOR_NVIDIA ; 

__attribute__((used)) static const WCHAR *get_installeddriver( UINT vendorid )
{
    static const WCHAR driver_amdW[] = {'a','t','i','c','f','x','3','2','.','d','l','l',0};
    static const WCHAR driver_intelW[] = {'i','g','d','u','m','d','i','m','3','2','.','d','l','l',0};
    static const WCHAR driver_nvidiaW[] = {'n','v','d','3','d','u','m','.','d','l','l',0};
    static const WCHAR driver_wineW[] = {'w','i','n','e','.','d','l','l',0};

    /* FIXME: wined3d has a better table, but we cannot access this information through dxgi */

    if (vendorid == HW_VENDOR_AMD)
        return driver_amdW;
    else if (vendorid == HW_VENDOR_NVIDIA)
        return driver_nvidiaW;
    else if (vendorid == HW_VENDOR_INTEL)
        return driver_intelW;
    return driver_wineW;
}