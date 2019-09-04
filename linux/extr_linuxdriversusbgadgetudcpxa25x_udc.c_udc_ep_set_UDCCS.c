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
struct pxa25x_ep {int /*<<< orphan*/  regoff_udccs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  udc_set_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void udc_ep_set_UDCCS(struct pxa25x_ep *ep, u32 data)
{
	udc_set_reg(ep->dev, data, ep->regoff_udccs);
}