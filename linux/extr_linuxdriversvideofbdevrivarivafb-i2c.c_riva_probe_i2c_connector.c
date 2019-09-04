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
typedef  int /*<<< orphan*/  u8 ;
struct riva_par {TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/ * fb_ddc_read (int /*<<< orphan*/ *) ; 

int riva_probe_i2c_connector(struct riva_par *par, int conn, u8 **out_edid)
{
	u8 *edid = NULL;

	if (par->chan[conn].par)
		edid = fb_ddc_read(&par->chan[conn].adapter);

	if (out_edid)
		*out_edid = edid;
	if (!edid)
		return 1;

	return 0;
}