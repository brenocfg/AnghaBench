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
struct fcoe_ctlr {int /*<<< orphan*/  sol_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIP_SC_VN_CLAIM_NOTIFY ; 
 int /*<<< orphan*/  fcoe_all_vn2vn ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_send (struct fcoe_ctlr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void fcoe_ctlr_vn_send_claim(struct fcoe_ctlr *fip)
{
	fcoe_ctlr_vn_send(fip, FIP_SC_VN_CLAIM_NOTIFY, fcoe_all_vn2vn, 0);
	fip->sol_time = jiffies;
}