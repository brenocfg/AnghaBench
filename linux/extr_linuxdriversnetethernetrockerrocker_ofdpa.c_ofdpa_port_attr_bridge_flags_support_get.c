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
struct rocker_port {int dummy; } ;

/* Variables and functions */
 unsigned long BR_LEARNING ; 

__attribute__((used)) static int
ofdpa_port_attr_bridge_flags_support_get(const struct rocker_port *
					 rocker_port,
					 unsigned long *
					 p_brport_flags_support)
{
	*p_brport_flags_support = BR_LEARNING;
	return 0;
}