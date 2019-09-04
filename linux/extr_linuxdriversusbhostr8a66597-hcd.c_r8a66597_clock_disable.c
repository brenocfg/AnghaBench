#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct r8a66597 {int /*<<< orphan*/  clk; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ on_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLLC ; 
 int /*<<< orphan*/  SCKE ; 
 int /*<<< orphan*/  SYSCFG0 ; 
 int /*<<< orphan*/  USBE ; 
 int /*<<< orphan*/  XCKE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void r8a66597_clock_disable(struct r8a66597 *r8a66597)
{
	r8a66597_bclr(r8a66597, SCKE, SYSCFG0);
	udelay(1);

	if (r8a66597->pdata->on_chip) {
		clk_disable_unprepare(r8a66597->clk);
	} else {
		r8a66597_bclr(r8a66597, PLLC, SYSCFG0);
		r8a66597_bclr(r8a66597, XCKE, SYSCFG0);
		r8a66597_bclr(r8a66597, USBE, SYSCFG0);
	}
}