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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct TYPE_3__ {int initiator; } ;
struct TYPE_4__ {int /*<<< orphan*/  rspcode; TYPE_1__ servparams; } ;
struct fc_prli_s {TYPE_2__ parampage; int /*<<< orphan*/  command; } ;
typedef  enum bfa_lport_role { ____Placeholder_bfa_lport_role } bfa_lport_role ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_ACC ; 
 int /*<<< orphan*/  FC_PRLI_ACC_XQTD ; 
 int /*<<< orphan*/  fc_els_rsp_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fc_prli_s*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prli_tmpl ; 

u16
fc_prli_acc_build(struct fchs_s *fchs, void *pld, u32 d_id, u32 s_id,
		  __be16 ox_id, enum bfa_lport_role role)
{
	struct fc_prli_s *prli = (struct fc_prli_s *) (pld);

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);
	memcpy(prli, &prli_tmpl, sizeof(struct fc_prli_s));

	prli->command = FC_ELS_ACC;

	prli->parampage.servparams.initiator = 1;

	prli->parampage.rspcode = FC_PRLI_ACC_XQTD;

	return sizeof(struct fc_prli_s);
}