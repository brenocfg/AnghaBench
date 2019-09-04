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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2i_endpoint {int /*<<< orphan*/  ep_cid; TYPE_1__* hba; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnic_dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2I_NX2_DEV_57710 ; 
 int /*<<< orphan*/  GET_CID_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 bnx2i_get_cid_num(struct bnx2i_endpoint *ep)
{
	u32 cid;

	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		cid = ep->ep_cid;
	else
		cid = GET_CID_NUM(ep->ep_cid);
	return cid;
}