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
struct bfa_fcs_vport_s {int /*<<< orphan*/  qe; } ;
struct bfa_fcs_fabric_s {int /*<<< orphan*/  wc; int /*<<< orphan*/  num_vports; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
bfa_fcs_fabric_delvport(struct bfa_fcs_fabric_s *fabric,
			struct bfa_fcs_vport_s *vport)
{
	list_del(&vport->qe);
	fabric->num_vports--;
	bfa_wc_down(&fabric->wc);
}