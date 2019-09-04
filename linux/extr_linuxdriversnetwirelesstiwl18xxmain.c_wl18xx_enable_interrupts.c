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
typedef  int u32 ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_INTERRUPT_MASK ; 
 int WL1271_ACX_INTR_ALL ; 
 int WL18XX_ACX_EVENTS_VECTOR ; 
 int WL18XX_INTR_MASK ; 
 int /*<<< orphan*/  wlcore_disable_interrupts (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_enable_interrupts (struct wl1271*) ; 
 int wlcore_write_reg (struct wl1271*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wl18xx_enable_interrupts(struct wl1271 *wl)
{
	u32 event_mask, intr_mask;
	int ret;

	event_mask = WL18XX_ACX_EVENTS_VECTOR;
	intr_mask = WL18XX_INTR_MASK;

	ret = wlcore_write_reg(wl, REG_INTERRUPT_MASK, event_mask);
	if (ret < 0)
		goto out;

	wlcore_enable_interrupts(wl);

	ret = wlcore_write_reg(wl, REG_INTERRUPT_MASK,
			       WL1271_ACX_INTR_ALL & ~intr_mask);
	if (ret < 0)
		goto disable_interrupts;

	return ret;

disable_interrupts:
	wlcore_disable_interrupts(wl);

out:
	return ret;
}