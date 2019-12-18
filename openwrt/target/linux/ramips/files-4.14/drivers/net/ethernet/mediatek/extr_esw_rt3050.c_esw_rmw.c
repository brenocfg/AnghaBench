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
struct rt305x_esw {int /*<<< orphan*/  reg_rw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  esw_rmw_raw (struct rt305x_esw*,unsigned int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void esw_rmw(struct rt305x_esw *esw, unsigned reg,
		    unsigned long mask, unsigned long val)
{
	unsigned long flags;

	spin_lock_irqsave(&esw->reg_rw_lock, flags);
	esw_rmw_raw(esw, reg, mask, val);
	spin_unlock_irqrestore(&esw->reg_rw_lock, flags);
}