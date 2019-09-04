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
typedef  int /*<<< orphan*/  u32 ;
struct dispc_reg_field {int /*<<< orphan*/  low; int /*<<< orphan*/  high; int /*<<< orphan*/  reg; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
typedef  enum mgr_reg_fields { ____Placeholder_mgr_reg_fields } mgr_reg_fields ;
struct TYPE_2__ {struct dispc_reg_field* reg_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mgr_desc ; 

__attribute__((used)) static u32 mgr_fld_read(enum omap_channel channel, enum mgr_reg_fields regfld)
{
	const struct dispc_reg_field rfld = mgr_desc[channel].reg_desc[regfld];
	return REG_GET(rfld.reg, rfld.high, rfld.low);
}