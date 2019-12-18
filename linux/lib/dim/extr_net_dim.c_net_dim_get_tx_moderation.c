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
typedef  size_t u8 ;
struct dim_cq_moder {size_t cq_period_mode; } ;

/* Variables and functions */
 struct dim_cq_moder** tx_profile ; 

struct dim_cq_moder
net_dim_get_tx_moderation(u8 cq_period_mode, int ix)
{
	struct dim_cq_moder cq_moder = tx_profile[cq_period_mode][ix];

	cq_moder.cq_period_mode = cq_period_mode;
	return cq_moder;
}