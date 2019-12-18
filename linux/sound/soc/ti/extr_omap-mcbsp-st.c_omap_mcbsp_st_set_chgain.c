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
struct omap_mcbsp_st_data {scalar_t__ enabled; void* ch1gain; void* ch0gain; } ;
struct omap_mcbsp {int /*<<< orphan*/  lock; struct omap_mcbsp_st_data* st_data; } ;
typedef  void* s16 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  omap_mcbsp_st_chgain (struct omap_mcbsp*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_mcbsp_st_set_chgain(struct omap_mcbsp *mcbsp, int channel,
				    s16 chgain)
{
	struct omap_mcbsp_st_data *st_data = mcbsp->st_data;
	int ret = 0;

	if (!st_data)
		return -ENOENT;

	spin_lock_irq(&mcbsp->lock);
	if (channel == 0)
		st_data->ch0gain = chgain;
	else if (channel == 1)
		st_data->ch1gain = chgain;
	else
		ret = -EINVAL;

	if (st_data->enabled)
		omap_mcbsp_st_chgain(mcbsp);
	spin_unlock_irq(&mcbsp->lock);

	return ret;
}