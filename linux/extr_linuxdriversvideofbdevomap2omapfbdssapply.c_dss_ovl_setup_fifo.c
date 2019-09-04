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
struct ovl_priv_data {int /*<<< orphan*/  enabling; int /*<<< orphan*/  enabled; } ;
struct omap_overlay {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_ovl_compute_fifo_thresholds (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_apply_ovl_fifo_thresholds (struct omap_overlay*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ovl_priv_data* get_ovl_priv (struct omap_overlay*) ; 
 int /*<<< orphan*/  ovl_manual_update (struct omap_overlay*) ; 

__attribute__((used)) static void dss_ovl_setup_fifo(struct omap_overlay *ovl)
{
	struct ovl_priv_data *op = get_ovl_priv(ovl);
	u32 fifo_low, fifo_high;
	bool use_fifo_merge = false;

	if (!op->enabled && !op->enabling)
		return;

	dispc_ovl_compute_fifo_thresholds(ovl->id, &fifo_low, &fifo_high,
			use_fifo_merge, ovl_manual_update(ovl));

	dss_apply_ovl_fifo_thresholds(ovl, fifo_low, fifo_high);
}