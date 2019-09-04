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
struct bnx2i_hba {int /*<<< orphan*/  cnic_dev_type; } ;
struct bnx2i_endpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2I_NX2_DEV_57710 ; 
 int bnx2i_570x_send_conn_ofld_req (struct bnx2i_hba*,struct bnx2i_endpoint*) ; 
 int bnx2i_5771x_send_conn_ofld_req (struct bnx2i_hba*,struct bnx2i_endpoint*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2i_send_conn_ofld_req(struct bnx2i_hba *hba, struct bnx2i_endpoint *ep)
{
	int rc;

	if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type))
		rc = bnx2i_5771x_send_conn_ofld_req(hba, ep);
	else
		rc = bnx2i_570x_send_conn_ofld_req(hba, ep);

	return rc;
}