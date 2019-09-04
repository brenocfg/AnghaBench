#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct vnic_wq_copy {int dummy; } ;
struct TYPE_9__ {scalar_t__ _resvd2; int /*<<< orphan*/  ha_mac; void* e_d_tov; void* r_a_tov; scalar_t__ _resvd1; int /*<<< orphan*/  fcf_mac; int /*<<< orphan*/  s_id; scalar_t__ _resvd0; } ;
struct TYPE_10__ {TYPE_4__ flogi_fip_reg; } ;
struct TYPE_6__ {void* req_id; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct TYPE_8__ {TYPE_2__ tag; scalar_t__ _resvd; scalar_t__ status; int /*<<< orphan*/  type; } ;
struct fcpio_host_req {TYPE_5__ u; TYPE_3__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FCPIO_FLOGI_FIP_REG ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fcpio_host_req* vnic_wq_copy_next_desc (struct vnic_wq_copy*) ; 
 int /*<<< orphan*/  vnic_wq_copy_post (struct vnic_wq_copy*) ; 

__attribute__((used)) static inline void fnic_queue_wq_copy_desc_fip_reg(struct vnic_wq_copy *wq,
						   u32 req_id, u32 s_id,
						   u8 *fcf_mac, u8 *ha_mac,
						   u32 r_a_tov, u32 e_d_tov)
{
	struct fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_FLOGI_FIP_REG; /* enum fcpio_type */
	desc->hdr.status = 0;                 /* header status entry */
	desc->hdr._resvd = 0;                 /* reserved */
	desc->hdr.tag.u.req_id = req_id;      /* id for this request */

	desc->u.flogi_fip_reg._resvd0 = 0;
	hton24(desc->u.flogi_fip_reg.s_id, s_id);
	memcpy(desc->u.flogi_fip_reg.fcf_mac, fcf_mac, ETH_ALEN);
	desc->u.flogi_fip_reg._resvd1 = 0;
	desc->u.flogi_fip_reg.r_a_tov = r_a_tov;
	desc->u.flogi_fip_reg.e_d_tov = e_d_tov;
	memcpy(desc->u.flogi_fip_reg.ha_mac, ha_mac, ETH_ALEN);
	desc->u.flogi_fip_reg._resvd2 = 0;

	vnic_wq_copy_post(wq);
}