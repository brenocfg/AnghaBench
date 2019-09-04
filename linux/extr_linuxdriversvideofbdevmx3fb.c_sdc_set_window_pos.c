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
struct mx3fb_data {scalar_t__ v_start_width; scalar_t__ h_start_width; } ;
typedef  int int16_t ;
typedef  enum ipu_channel { ____Placeholder_ipu_channel } ipu_channel ;

/* Variables and functions */
 int EINVAL ; 
 int IDMAC_SDC_0 ; 
 int /*<<< orphan*/  SDC_BG_POS ; 
 int /*<<< orphan*/  mx3fb_write_reg (struct mx3fb_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdc_set_window_pos(struct mx3fb_data *mx3fb, enum ipu_channel channel,
			      int16_t x_pos, int16_t y_pos)
{
	if (channel != IDMAC_SDC_0)
		return -EINVAL;

	x_pos += mx3fb->h_start_width;
	y_pos += mx3fb->v_start_width;

	mx3fb_write_reg(mx3fb, (x_pos << 16) | y_pos, SDC_BG_POS);
	return 0;
}