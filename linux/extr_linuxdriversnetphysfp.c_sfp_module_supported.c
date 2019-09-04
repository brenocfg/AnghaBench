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
struct TYPE_2__ {scalar_t__ phys_id; scalar_t__ phys_ext_id; } ;
struct sfp_eeprom_id {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ SFP_PHYS_EXT_ID_SFP ; 
 scalar_t__ SFP_PHYS_ID_SFP ; 

__attribute__((used)) static bool sfp_module_supported(const struct sfp_eeprom_id *id)
{
	return id->base.phys_id == SFP_PHYS_ID_SFP &&
	       id->base.phys_ext_id == SFP_PHYS_EXT_ID_SFP;
}