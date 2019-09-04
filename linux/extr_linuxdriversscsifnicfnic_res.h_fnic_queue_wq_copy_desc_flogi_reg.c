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
typedef  int /*<<< orphan*/  u32 ;
struct vnic_wq_copy {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  gateway_mac; int /*<<< orphan*/  s_id; scalar_t__ _resvd; int /*<<< orphan*/  format; } ;
struct TYPE_10__ {TYPE_4__ flogi_reg; } ;
struct TYPE_6__ {int /*<<< orphan*/  req_id; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct TYPE_8__ {TYPE_2__ tag; scalar_t__ _resvd; scalar_t__ status; int /*<<< orphan*/  type; } ;
struct fcpio_host_req {TYPE_5__ u; TYPE_3__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FCPIO_FLOGI_REG ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fcpio_host_req* vnic_wq_copy_next_desc (struct vnic_wq_copy*) ; 
 int /*<<< orphan*/  vnic_wq_copy_post (struct vnic_wq_copy*) ; 

__attribute__((used)) static inline void fnic_queue_wq_copy_desc_flogi_reg(struct vnic_wq_copy *wq,
						     u32 req_id, u8 format,
						     u32 s_id, u8 *gw_mac)
{
	struct fcpio_host_req *desc = vnic_wq_copy_next_desc(wq);

	desc->hdr.type = FCPIO_FLOGI_REG;     /* enum fcpio_type */
	desc->hdr.status = 0;                 /* header status entry */
	desc->hdr._resvd = 0;                 /* reserved */
	desc->hdr.tag.u.req_id = req_id;      /* id for this request */

	desc->u.flogi_reg.format = format;
	desc->u.flogi_reg._resvd = 0;
	hton24(desc->u.flogi_reg.s_id, s_id);
	memcpy(desc->u.flogi_reg.gateway_mac, gw_mac, ETH_ALEN);

	vnic_wq_copy_post(wq);
}