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
struct fc_rnid_general_topology_data_s {void* num_attached_nodes; scalar_t__ phy_port_num; void* asso_type; } ;
struct bfa_fcs_lport_s {int dummy; } ;

/* Variables and functions */
 int RNID_ASSOCIATED_TYPE_HOST ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fc_rnid_general_topology_data_s*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fs_port_get_gen_topo_data(struct bfa_fcs_lport_s *port,
			struct fc_rnid_general_topology_data_s *gen_topo_data)
{
	memset(gen_topo_data, 0,
		      sizeof(struct fc_rnid_general_topology_data_s));

	gen_topo_data->asso_type = cpu_to_be32(RNID_ASSOCIATED_TYPE_HOST);
	gen_topo_data->phy_port_num = 0;	/* @todo */
	gen_topo_data->num_attached_nodes = cpu_to_be32(1);
}