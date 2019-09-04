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
struct bfa_rport_qos_attr_s {int dummy; } ;
struct TYPE_2__ {struct bfa_rport_qos_attr_s qos; } ;
struct bfa_rport_aen_data_s {TYPE_1__ priv; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  pwwn; int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_RPORT_AEN_QOS_PRIO ; 
 int /*<<< orphan*/  bfa_fcs_rport_aen_post (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ,struct bfa_rport_aen_data_s*) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_cb_rport_qos_scn_prio(void *cbarg,
		struct bfa_rport_qos_attr_s old_qos_attr,
		struct bfa_rport_qos_attr_s new_qos_attr)
{
	struct bfa_fcs_rport_s *rport = (struct bfa_fcs_rport_s *) cbarg;
	struct bfa_rport_aen_data_s aen_data;

	bfa_trc(rport->fcs, rport->pwwn);
	aen_data.priv.qos = new_qos_attr;
	bfa_fcs_rport_aen_post(rport, BFA_RPORT_AEN_QOS_PRIO, &aen_data);
}