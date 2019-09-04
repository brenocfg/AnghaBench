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
struct fchs_s {int rx_id; int /*<<< orphan*/  ox_id; } ;
struct fc_ba_acc_s {int rx_id; int /*<<< orphan*/  ox_id; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ba_acc_tmpl ; 
 int /*<<< orphan*/  fc_bls_rsp_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fc_ba_acc_s*,int /*<<< orphan*/ *,int) ; 

u16
fc_ba_acc_build(struct fchs_s *fchs, struct fc_ba_acc_s *ba_acc, u32 d_id,
		u32 s_id, __be16 ox_id, u16 rx_id)
{
	fc_bls_rsp_build(fchs, d_id, s_id, ox_id);

	memcpy(ba_acc, &ba_acc_tmpl, sizeof(struct fc_ba_acc_s));

	fchs->rx_id = rx_id;

	ba_acc->ox_id = fchs->ox_id;
	ba_acc->rx_id = fchs->rx_id;

	return sizeof(struct fc_ba_acc_s);
}