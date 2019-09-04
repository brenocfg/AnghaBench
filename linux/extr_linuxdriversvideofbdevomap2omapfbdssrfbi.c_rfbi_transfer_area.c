#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct omap_overlay_manager {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_6__ {int x_res; int y_res; } ;
struct TYPE_4__ {struct omap_overlay_manager* manager; } ;
struct TYPE_5__ {void (* framedone_callback ) (void*) ;int /*<<< orphan*/  te_enabled; void* framedone_callback_data; TYPE_3__ timings; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int) ; 
 int FLD_MOD (int,int,int,int) ; 
 int /*<<< orphan*/  RFBI_CONTROL ; 
 int /*<<< orphan*/  RFBI_PIXEL_CNT ; 
 int dss_mgr_enable (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_mgr_set_timings (struct omap_overlay_manager*,TYPE_3__*) ; 
 TYPE_2__ rfbi ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rfbi_transfer_area(struct omap_dss_device *dssdev,
		void (*callback)(void *data), void *data)
{
	u32 l;
	int r;
	struct omap_overlay_manager *mgr = rfbi.output.manager;
	u16 width = rfbi.timings.x_res;
	u16 height = rfbi.timings.y_res;

	/*BUG_ON(callback == 0);*/
	BUG_ON(rfbi.framedone_callback != NULL);

	DSSDBG("rfbi_transfer_area %dx%d\n", width, height);

	dss_mgr_set_timings(mgr, &rfbi.timings);

	r = dss_mgr_enable(mgr);
	if (r)
		return r;

	rfbi.framedone_callback = callback;
	rfbi.framedone_callback_data = data;

	rfbi_write_reg(RFBI_PIXEL_CNT, width * height);

	l = rfbi_read_reg(RFBI_CONTROL);
	l = FLD_MOD(l, 1, 0, 0); /* enable */
	if (!rfbi.te_enabled)
		l = FLD_MOD(l, 1, 4, 4); /* ITE */

	rfbi_write_reg(RFBI_CONTROL, l);

	return 0;
}