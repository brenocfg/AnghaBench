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
struct net_device {struct dsa_port* dsa_ptr; } ;
struct dsa_port {int index; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int dsa_master_get_phys_port_name(struct net_device *dev,
					 char *name, size_t len)
{
	struct dsa_port *cpu_dp = dev->dsa_ptr;

	if (snprintf(name, len, "p%d", cpu_dp->index) >= len)
		return -EINVAL;

	return 0;
}