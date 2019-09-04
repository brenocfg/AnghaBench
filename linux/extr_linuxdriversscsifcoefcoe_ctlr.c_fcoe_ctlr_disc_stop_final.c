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
struct fc_lport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_rport_flush_queue () ; 
 int /*<<< orphan*/  fcoe_ctlr_disc_stop (struct fc_lport*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void fcoe_ctlr_disc_stop_final(struct fc_lport *lport)
{
	fcoe_ctlr_disc_stop(lport);
	fc_rport_flush_queue();
	synchronize_rcu();
}