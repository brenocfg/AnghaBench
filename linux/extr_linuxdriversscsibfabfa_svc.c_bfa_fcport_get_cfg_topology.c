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
struct bfa_s {int dummy; } ;
struct TYPE_2__ {int topology; } ;
struct bfa_fcport_s {TYPE_1__ cfg; } ;
typedef  enum bfa_port_topology { ____Placeholder_bfa_port_topology } bfa_port_topology ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (struct bfa_s*) ; 

enum bfa_port_topology
bfa_fcport_get_cfg_topology(struct bfa_s *bfa)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	return fcport->cfg.topology;
}