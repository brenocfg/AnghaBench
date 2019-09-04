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
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int dummy; } ;
struct fc_els_cmd_s {int els_code; } ;
struct bfa_fcs_fabric_s {int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
#define  FC_ELS_FLOGI 128 
 int /*<<< orphan*/  bfa_fcs_fabric_process_flogi (struct bfa_fcs_fabric_s*,struct fchs_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_fabric_process_uf(struct bfa_fcs_fabric_s *fabric, struct fchs_s *fchs,
			  u16 len)
{
	struct fc_els_cmd_s *els_cmd = (struct fc_els_cmd_s *) (fchs + 1);

	bfa_trc(fabric->fcs, els_cmd->els_code);

	switch (els_cmd->els_code) {
	case FC_ELS_FLOGI:
		bfa_fcs_fabric_process_flogi(fabric, fchs, len);
		break;

	default:
		/*
		 * need to generate a LS_RJT
		 */
		break;
	}
}