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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct fcgs_rspnid_req_s {int /*<<< orphan*/  spn; scalar_t__ spn_len; int /*<<< orphan*/  dap; } ;
struct ct_hdr_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_NAME_SERVER ; 
 int /*<<< orphan*/  GS_RSPN_ID ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_cthdr_build (struct ct_hdr_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_fchdr_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fcgs_rspnid_req_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

u16
fc_rspnid_build(struct fchs_s *fchs, void *pyld, u32 s_id, u16 ox_id,
		u8 *name)
{

	struct ct_hdr_s *cthdr = (struct ct_hdr_s *) pyld;
	struct fcgs_rspnid_req_s *rspnid =
			(struct fcgs_rspnid_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_RSPN_ID);

	memset(rspnid, 0, sizeof(struct fcgs_rspnid_req_s));

	rspnid->dap = s_id;
	strlcpy(rspnid->spn, name, sizeof(rspnid->spn));
	rspnid->spn_len = (u8) strlen(rspnid->spn);

	return sizeof(struct fcgs_rspnid_req_s) + sizeof(struct ct_hdr_s);
}