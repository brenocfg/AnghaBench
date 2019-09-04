#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtl8169_private {size_t mac_version; } ;
struct TYPE_2__ {char const* fw_name; } ;

/* Variables and functions */
 TYPE_1__* rtl_chip_infos ; 

__attribute__((used)) static const char *rtl_lookup_firmware_name(struct rtl8169_private *tp)
{
	return rtl_chip_infos[tp->mac_version].fw_name;
}