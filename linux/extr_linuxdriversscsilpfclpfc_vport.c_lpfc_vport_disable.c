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
struct fc_vport {int dummy; } ;

/* Variables and functions */
 int disable_vport (struct fc_vport*) ; 
 int enable_vport (struct fc_vport*) ; 

int
lpfc_vport_disable(struct fc_vport *fc_vport, bool disable)
{
	if (disable)
		return disable_vport(fc_vport);
	else
		return enable_vport(fc_vport);
}