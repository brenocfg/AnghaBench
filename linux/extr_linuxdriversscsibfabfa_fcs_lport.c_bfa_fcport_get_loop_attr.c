#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_7__ {size_t* alpa_pos_map; size_t num_alpa; int /*<<< orphan*/  alpabm_valid; } ;
struct TYPE_8__ {TYPE_3__ ploop; } ;
struct bfa_fcs_lport_s {TYPE_4__ port_topo; TYPE_2__* fcs; int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {size_t* alpa_bm; } ;
struct bfa_fcport_s {TYPE_1__ alpabm; int /*<<< orphan*/  myalpa; int /*<<< orphan*/  alpabm_valid; } ;
struct TYPE_6__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (int /*<<< orphan*/ ) ; 
 int FC_ALPA_MAX ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,size_t) ; 
 size_t* loop_alpa_map ; 

void
bfa_fcport_get_loop_attr(struct bfa_fcs_lport_s *port)
{
	int i = 0, j = 0, bit = 0, alpa_bit = 0;
	u8 k = 0;
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(port->fcs->bfa);

	port->port_topo.ploop.alpabm_valid = fcport->alpabm_valid;
	port->pid = fcport->myalpa;
	port->pid = bfa_hton3b(port->pid);

	for (i = 0; i < (FC_ALPA_MAX / 8); i++) {
		for (j = 0, alpa_bit = 0; j < 8; j++, alpa_bit++) {
			bfa_trc(port->fcs->bfa, fcport->alpabm.alpa_bm[i]);
			bit = (fcport->alpabm.alpa_bm[i] & (1 << (7 - j)));
			if (bit) {
				port->port_topo.ploop.alpa_pos_map[k] =
					loop_alpa_map[(i * 8) + alpa_bit];
				k++;
				bfa_trc(port->fcs->bfa, k);
				bfa_trc(port->fcs->bfa,
					 port->port_topo.ploop.alpa_pos_map[k]);
			}
		}
	}
	port->port_topo.ploop.num_alpa = k;
}