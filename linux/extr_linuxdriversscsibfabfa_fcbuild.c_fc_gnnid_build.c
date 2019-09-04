#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct ct_hdr_s {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dap; } ;
typedef  TYPE_1__ fcgs_gnnid_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_NAME_SERVER ; 
 int /*<<< orphan*/  GS_GNN_ID ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_cthdr_build (struct ct_hdr_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_fchdr_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

u16
fc_gnnid_build(struct fchs_s *fchs, void *pyld, u32 s_id, u16 ox_id,
	       u32 port_id)
{
	struct ct_hdr_s *cthdr = (struct ct_hdr_s *) pyld;
	fcgs_gnnid_req_t *gnnid = (fcgs_gnnid_req_t *) (cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_GNN_ID);

	memset(gnnid, 0, sizeof(fcgs_gnnid_req_t));
	gnnid->dap = port_id;
	return sizeof(fcgs_gnnid_req_t) + sizeof(struct ct_hdr_s);
}