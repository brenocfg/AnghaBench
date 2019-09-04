#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int options; } ;
struct TYPE_4__ {TYPE_1__ ext; } ;
struct sfp {TYPE_2__ id; } ;

/* Variables and functions */
 unsigned int SFP_E_LOS_HIGH ; 
 unsigned int SFP_E_LOS_LOW ; 
 int /*<<< orphan*/  SFP_OPTIONS_LOS_INVERTED ; 
 int /*<<< orphan*/  SFP_OPTIONS_LOS_NORMAL ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sfp_los_event_inactive(struct sfp *sfp, unsigned int event)
{
	return (sfp->id.ext.options & cpu_to_be16(SFP_OPTIONS_LOS_INVERTED) &&
		event == SFP_E_LOS_HIGH) ||
	       (sfp->id.ext.options & cpu_to_be16(SFP_OPTIONS_LOS_NORMAL) &&
		event == SFP_E_LOS_LOW);
}