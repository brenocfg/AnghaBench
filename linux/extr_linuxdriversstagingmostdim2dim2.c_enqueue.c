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
struct most_interface {int dummy; } ;
struct mbo {scalar_t__ bus_address; int /*<<< orphan*/  list; } ;
struct hdm_channel {int /*<<< orphan*/  pending_list; int /*<<< orphan*/  is_initialized; } ;
struct dim2_hdm {struct hdm_channel* hch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_CHANNELS ; 
 int EFAULT ; 
 int EPERM ; 
 int /*<<< orphan*/  dim_lock ; 
 struct dim2_hdm* iface_to_hdm (struct most_interface*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_start_dim_transfer (struct hdm_channel*) ; 

__attribute__((used)) static int enqueue(struct most_interface *most_iface, int ch_idx,
		   struct mbo *mbo)
{
	struct dim2_hdm *dev = iface_to_hdm(most_iface);
	struct hdm_channel *hdm_ch = dev->hch + ch_idx;
	unsigned long flags;

	BUG_ON(ch_idx < 0 || ch_idx >= DMA_CHANNELS);

	if (!hdm_ch->is_initialized)
		return -EPERM;

	if (mbo->bus_address == 0)
		return -EFAULT;

	spin_lock_irqsave(&dim_lock, flags);
	list_add_tail(&mbo->list, &hdm_ch->pending_list);
	spin_unlock_irqrestore(&dim_lock, flags);

	(void)try_start_dim_transfer(hdm_ch);

	return 0;
}