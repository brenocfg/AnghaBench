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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  dwc_otg_core_if_t ;

/* Variables and functions */
 scalar_t__ DWC_HOST_MODE ; 
 scalar_t__ dwc_otg_mode (int /*<<< orphan*/ *) ; 

uint8_t dwc_otg_is_device_mode(dwc_otg_core_if_t * _core_if)
{
	return (dwc_otg_mode(_core_if) != DWC_HOST_MODE);
}