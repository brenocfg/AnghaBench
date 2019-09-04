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
struct timer_list {int dummy; } ;
struct radeonfb_info {int /*<<< orphan*/  pending_lvds_gen_cntl; } ;

/* Variables and functions */
 int /*<<< orphan*/  LVDS_GEN_CNTL ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeonfb_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lvds_timer ; 
 int /*<<< orphan*/  radeon_engine_idle () ; 
 struct radeonfb_info* rinfo ; 

__attribute__((used)) static void radeon_lvds_timer_func(struct timer_list *t)
{
	struct radeonfb_info *rinfo = from_timer(rinfo, t, lvds_timer);

	radeon_engine_idle();

	OUTREG(LVDS_GEN_CNTL, rinfo->pending_lvds_gen_cntl);
}