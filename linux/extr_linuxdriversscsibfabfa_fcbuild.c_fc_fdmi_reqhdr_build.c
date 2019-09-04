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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct ct_hdr_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_MGMT_SERVER ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_fchdr_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_gs_fdmi_cthdr_build (struct ct_hdr_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_fdmi_reqhdr_build(struct fchs_s *fchs, void *pyld, u32 s_id,
		     u16 cmd_code)
{

	struct ct_hdr_s *cthdr = (struct ct_hdr_s *) pyld;
	u32        d_id = bfa_hton3b(FC_MGMT_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_fdmi_cthdr_build(cthdr, s_id, cmd_code);

	return sizeof(struct ct_hdr_s);
}