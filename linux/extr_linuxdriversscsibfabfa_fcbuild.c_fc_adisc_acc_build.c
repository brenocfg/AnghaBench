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
typedef  int /*<<< orphan*/  wwn_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int dummy; } ;
struct fc_adisc_s {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_ACC ; 
 int /*<<< orphan*/  fc_adisc_x_build (struct fchs_s*,struct fc_adisc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16
fc_adisc_acc_build(struct fchs_s *fchs, struct fc_adisc_s *adisc, u32 d_id,
		   u32 s_id, __be16 ox_id, wwn_t port_name,
		   wwn_t node_name)
{
	return fc_adisc_x_build(fchs, adisc, d_id, s_id, ox_id, port_name,
				node_name, FC_ELS_ACC);
}