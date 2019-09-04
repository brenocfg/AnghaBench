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
typedef  size_t u32 ;
struct dwc2_hsotg_ep {int dummy; } ;
struct dwc2_hsotg {struct dwc2_hsotg_ep** eps_out; struct dwc2_hsotg_ep** eps_in; } ;

/* Variables and functions */

__attribute__((used)) static inline struct dwc2_hsotg_ep *index_to_ep(struct dwc2_hsotg *hsotg,
						u32 ep_index, u32 dir_in)
{
	if (dir_in)
		return hsotg->eps_in[ep_index];
	else
		return hsotg->eps_out[ep_index];
}