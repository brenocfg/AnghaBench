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
struct TYPE_2__ {int /*<<< orphan*/  logo_sent; } ;
struct bfa_fcs_vport_s {int /*<<< orphan*/  lps; TYPE_1__ vport_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vport_fcs (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  __vport_pwwn (struct bfa_fcs_vport_s*) ; 
 int /*<<< orphan*/  bfa_lps_fdisclogo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_vport_do_logo(struct bfa_fcs_vport_s *vport)
{
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));

	vport->vport_stats.logo_sent++;
	bfa_lps_fdisclogo(vport->lps);
}