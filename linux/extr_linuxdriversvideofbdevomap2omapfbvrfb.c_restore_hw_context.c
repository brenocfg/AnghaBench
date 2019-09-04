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
struct TYPE_2__ {int /*<<< orphan*/  physical_ba; int /*<<< orphan*/  size; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 TYPE_1__* ctxs ; 
 int /*<<< orphan*/  omap2_sms_write_rot_control (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap2_sms_write_rot_physical_ba (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap2_sms_write_rot_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void restore_hw_context(int ctx)
{
	omap2_sms_write_rot_control(ctxs[ctx].control, ctx);
	omap2_sms_write_rot_size(ctxs[ctx].size, ctx);
	omap2_sms_write_rot_physical_ba(ctxs[ctx].physical_ba, ctx);
}