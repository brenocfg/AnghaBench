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
struct xt_action_param {int hotdrop; void const* targinfo; void* target; } ;

/* Variables and functions */

__attribute__((used)) static inline void
nft_compat_set_par(struct xt_action_param *par, void *xt, const void *xt_info)
{
	par->target	= xt;
	par->targinfo	= xt_info;
	par->hotdrop	= false;
}