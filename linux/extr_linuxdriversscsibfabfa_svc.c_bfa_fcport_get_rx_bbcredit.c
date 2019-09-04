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
typedef  int /*<<< orphan*/  u8 ;
struct bfa_s {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bbcredit; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 TYPE_2__* BFA_FCPORT_MOD (struct bfa_s*) ; 
 scalar_t__ BFA_PORT_TOPOLOGY_LOOP ; 
 scalar_t__ bfa_fcport_get_topology (struct bfa_s*) ; 

u8
bfa_fcport_get_rx_bbcredit(struct bfa_s *bfa)
{
	if (bfa_fcport_get_topology(bfa) != BFA_PORT_TOPOLOGY_LOOP)
		return (BFA_FCPORT_MOD(bfa))->cfg.rx_bbcredit;

	else
		return 0;
}