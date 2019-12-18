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
typedef  int devnames_name ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int /*<<< orphan*/  wOutputOffset; int /*<<< orphan*/  wDeviceOffset; int /*<<< orphan*/  wDriverOffset; } ;
typedef  TYPE_1__ DEVNAMES ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
#define  devnames_device_name 130 
#define  devnames_driver_name 129 
#define  devnames_output_name 128 

__attribute__((used)) static inline WORD get_devname_offset(const DEVNAMES *dn, devnames_name which)
{
    switch(which)
    {
    case devnames_driver_name: return dn->wDriverOffset;
    case devnames_device_name: return dn->wDeviceOffset;
    case devnames_output_name: return dn->wOutputOffset;
    }
    ERR("Shouldn't be here\n");
    return 0;
}