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
struct target_fabric_configfs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  target_fabric_setup_discovery_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_attrib_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_auth_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_base_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_lun_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_mappedlun_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_mappedlun_stat_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_nacl_attrib_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_nacl_auth_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_nacl_base_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_nacl_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_nacl_param_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_nacl_stat_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_np_base_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_np_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_param_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_port_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_tpg_port_stat_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_wwn_cit (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  target_fabric_setup_wwn_fabric_stats_cit (struct target_fabric_configfs*) ; 

int target_fabric_setup_cits(struct target_fabric_configfs *tf)
{
	target_fabric_setup_discovery_cit(tf);
	target_fabric_setup_wwn_cit(tf);
	target_fabric_setup_wwn_fabric_stats_cit(tf);
	target_fabric_setup_tpg_cit(tf);
	target_fabric_setup_tpg_base_cit(tf);
	target_fabric_setup_tpg_port_cit(tf);
	target_fabric_setup_tpg_port_stat_cit(tf);
	target_fabric_setup_tpg_lun_cit(tf);
	target_fabric_setup_tpg_np_cit(tf);
	target_fabric_setup_tpg_np_base_cit(tf);
	target_fabric_setup_tpg_attrib_cit(tf);
	target_fabric_setup_tpg_auth_cit(tf);
	target_fabric_setup_tpg_param_cit(tf);
	target_fabric_setup_tpg_nacl_cit(tf);
	target_fabric_setup_tpg_nacl_base_cit(tf);
	target_fabric_setup_tpg_nacl_attrib_cit(tf);
	target_fabric_setup_tpg_nacl_auth_cit(tf);
	target_fabric_setup_tpg_nacl_param_cit(tf);
	target_fabric_setup_tpg_nacl_stat_cit(tf);
	target_fabric_setup_tpg_mappedlun_cit(tf);
	target_fabric_setup_tpg_mappedlun_stat_cit(tf);

	return 0;
}