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
struct dim_cq_moder {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIM_CQ_PERIOD_MODE_START_FROM_CQE ; 
 scalar_t__ NET_DIM_DEF_PROFILE_CQE ; 
 scalar_t__ NET_DIM_DEF_PROFILE_EQE ; 
 struct dim_cq_moder net_dim_get_rx_moderation (scalar_t__,scalar_t__) ; 

struct dim_cq_moder
net_dim_get_def_rx_moderation(u8 cq_period_mode)
{
	u8 profile_ix = cq_period_mode == DIM_CQ_PERIOD_MODE_START_FROM_CQE ?
			NET_DIM_DEF_PROFILE_CQE : NET_DIM_DEF_PROFILE_EQE;

	return net_dim_get_rx_moderation(cq_period_mode, profile_ix);
}