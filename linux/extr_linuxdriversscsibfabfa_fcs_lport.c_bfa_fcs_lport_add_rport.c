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
struct bfa_fcs_rport_s {int /*<<< orphan*/  qe; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  num_rports; int /*<<< orphan*/  rport_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_fcs_lport_add_rport(
	struct bfa_fcs_lport_s *port,
	struct bfa_fcs_rport_s *rport)
{
	list_add_tail(&rport->qe, &port->rport_q);
	port->num_rports++;
}