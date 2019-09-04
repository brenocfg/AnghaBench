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
struct rcar_gen3_chan {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ USB2_ADPCTRL ; 
 int USB2_ADPCTRL_IDDIG ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static bool rcar_gen3_check_id(struct rcar_gen3_chan *ch)
{
	return !!(readl(ch->base + USB2_ADPCTRL) & USB2_ADPCTRL_IDDIG);
}