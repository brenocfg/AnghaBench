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
typedef  enum arm_spe_pkt_type { ____Placeholder_arm_spe_pkt_type } arm_spe_pkt_type ;

/* Variables and functions */
 char const** arm_spe_packet_name ; 

const char *arm_spe_pkt_name(enum arm_spe_pkt_type type)
{
	return arm_spe_packet_name[type];
}