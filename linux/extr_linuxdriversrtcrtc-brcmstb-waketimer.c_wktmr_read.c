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
typedef  scalar_t__ u32 ;
struct wktmr_time {scalar_t__ pre; scalar_t__ sec; } ;
struct brcmstb_waketmr {scalar_t__ rate; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ BRCMSTB_WKTMR_COUNTER ; 
 scalar_t__ BRCMSTB_WKTMR_PRESCALER_VAL ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void wktmr_read(struct brcmstb_waketmr *timer,
		       struct wktmr_time *t)
{
	u32 tmp;

	do {
		t->sec = readl_relaxed(timer->base + BRCMSTB_WKTMR_COUNTER);
		tmp = readl_relaxed(timer->base + BRCMSTB_WKTMR_PRESCALER_VAL);
	} while (tmp >= timer->rate);

	t->pre = timer->rate - tmp;
}