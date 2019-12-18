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
struct omap_mcbsp_st_data {int enabled; } ;
struct omap_mcbsp {int /*<<< orphan*/  lock; struct omap_mcbsp_st_data* st_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  omap_mcbsp_st_start (struct omap_mcbsp*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_mcbsp_st_enable(struct omap_mcbsp *mcbsp)
{
	struct omap_mcbsp_st_data *st_data = mcbsp->st_data;

	if (!st_data)
		return -ENODEV;

	spin_lock_irq(&mcbsp->lock);
	st_data->enabled = 1;
	omap_mcbsp_st_start(mcbsp);
	spin_unlock_irq(&mcbsp->lock);

	return 0;
}