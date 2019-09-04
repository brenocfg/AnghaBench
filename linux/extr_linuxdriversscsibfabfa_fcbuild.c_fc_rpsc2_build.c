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
struct TYPE_3__ {int /*<<< orphan*/  els_code; } ;
struct fc_rpsc2_cmd_s {TYPE_2__* pid_list; int /*<<< orphan*/  num_pids; int /*<<< orphan*/  token; TYPE_1__ els_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_BRCD_TOKEN ; 
 int /*<<< orphan*/  FC_DOMAIN_CTRLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_ELS_RPSC ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_rpsc2_cmd_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_rpsc2_build(struct fchs_s *fchs, struct fc_rpsc2_cmd_s *rpsc2, u32 d_id,
		u32 s_id, u32 *pid_list, u16 npids)
{
	u32 dctlr_id = FC_DOMAIN_CTRLR(bfa_hton3b(d_id));
	int i = 0;

	fc_els_req_build(fchs, bfa_hton3b(dctlr_id), s_id, 0);

	memset(rpsc2, 0, sizeof(struct fc_rpsc2_cmd_s));

	rpsc2->els_cmd.els_code = FC_ELS_RPSC;
	rpsc2->token = cpu_to_be32(FC_BRCD_TOKEN);
	rpsc2->num_pids  = cpu_to_be16(npids);
	for (i = 0; i < npids; i++)
		rpsc2->pid_list[i].pid = pid_list[i];

	return sizeof(struct fc_rpsc2_cmd_s) + ((npids - 1) * (sizeof(u32)));
}