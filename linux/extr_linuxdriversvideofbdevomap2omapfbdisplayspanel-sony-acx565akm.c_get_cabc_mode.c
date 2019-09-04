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
struct panel_drv_data {int cabc_mode; } ;

/* Variables and functions */

__attribute__((used)) static unsigned get_cabc_mode(struct panel_drv_data *ddata)
{
	return ddata->cabc_mode;
}