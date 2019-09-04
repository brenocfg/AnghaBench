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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct mx3fb_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDC_COM_CONF ; 
 int SDC_COM_GLB_A ; 
 int /*<<< orphan*/  SDC_GW_CTRL ; 
 int mx3fb_read_reg (struct mx3fb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx3fb_write_reg (struct mx3fb_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sdc_set_global_alpha(struct mx3fb_data *mx3fb, bool enable, uint8_t alpha)
{
	uint32_t reg;
	unsigned long lock_flags;

	spin_lock_irqsave(&mx3fb->lock, lock_flags);

	if (enable) {
		reg = mx3fb_read_reg(mx3fb, SDC_GW_CTRL) & 0x00FFFFFFL;
		mx3fb_write_reg(mx3fb, reg | ((uint32_t) alpha << 24), SDC_GW_CTRL);

		reg = mx3fb_read_reg(mx3fb, SDC_COM_CONF);
		mx3fb_write_reg(mx3fb, reg | SDC_COM_GLB_A, SDC_COM_CONF);
	} else {
		reg = mx3fb_read_reg(mx3fb, SDC_COM_CONF);
		mx3fb_write_reg(mx3fb, reg & ~SDC_COM_GLB_A, SDC_COM_CONF);
	}

	spin_unlock_irqrestore(&mx3fb->lock, lock_flags);

	return 0;
}