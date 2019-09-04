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
struct tcx_thc {int dummy; } ;
struct tcx_tec {int dummy; } ;
struct tcx_par {scalar_t__ cplane; scalar_t__ bt; scalar_t__ thc; scalar_t__ tec; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;
struct TYPE_2__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ screen_base; } ;
struct bt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void tcx_unmap_regs(struct platform_device *op, struct fb_info *info,
			   struct tcx_par *par)
{
	if (par->tec)
		of_iounmap(&op->resource[7],
			   par->tec, sizeof(struct tcx_tec));
	if (par->thc)
		of_iounmap(&op->resource[9],
			   par->thc, sizeof(struct tcx_thc));
	if (par->bt)
		of_iounmap(&op->resource[8],
			   par->bt, sizeof(struct bt_regs));
	if (par->cplane)
		of_iounmap(&op->resource[4],
			   par->cplane, info->fix.smem_len * sizeof(u32));
	if (info->screen_base)
		of_iounmap(&op->resource[0],
			   info->screen_base, info->fix.smem_len);
}