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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct bfa_fcport_trunk_s {TYPE_1__ attr; } ;
struct TYPE_4__ {scalar_t__ topology; int /*<<< orphan*/  trunked; } ;
struct bfa_fcport_s {scalar_t__ topology; TYPE_2__ cfg; struct bfa_fcport_trunk_s trunk; } ;
struct bfa_bsg_gen_s {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 struct bfa_fcport_s* BFA_FCPORT_MOD (int /*<<< orphan*/ *) ; 
 scalar_t__ BFA_PORT_TOPOLOGY_LOOP ; 
 int BFA_STATUS_DPORT_ERR ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFA_TRUNK_DISABLED ; 
 int /*<<< orphan*/  BFA_TRUNK_OFFLINE ; 
 unsigned int IOCMD_TRUNK_DISABLE ; 
 unsigned int IOCMD_TRUNK_ENABLE ; 
 int /*<<< orphan*/  bfa_fcport_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcport_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcport_is_disabled (int /*<<< orphan*/ *) ; 
 scalar_t__ bfa_fcport_is_dport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_cfg_trunk(struct bfad_s *bfad, void *cmd, unsigned int v_cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)cmd;
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	struct bfa_fcport_trunk_s *trunk = &fcport->trunk;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	if (bfa_fcport_is_dport(&bfad->bfa)) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		return BFA_STATUS_DPORT_ERR;
	}

	if ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) ||
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	else {
		if (v_cmd == IOCMD_TRUNK_ENABLE) {
			trunk->attr.state = BFA_TRUNK_OFFLINE;
			bfa_fcport_disable(&bfad->bfa);
			fcport->cfg.trunked = BFA_TRUE;
		} else if (v_cmd == IOCMD_TRUNK_DISABLE) {
			trunk->attr.state = BFA_TRUNK_DISABLED;
			bfa_fcport_disable(&bfad->bfa);
			fcport->cfg.trunked = BFA_FALSE;
		}

		if (!bfa_fcport_is_disabled(&bfad->bfa))
			bfa_fcport_enable(&bfad->bfa);

		iocmd->status = BFA_STATUS_OK;
	}

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}