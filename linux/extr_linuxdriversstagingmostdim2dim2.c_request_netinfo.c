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
typedef  int u8 ;
struct most_interface {int dummy; } ;
struct mbo {int buffer_length; int* virt_address; } ;
struct dim2_hdm {void (* on_netinfo ) (struct most_interface*,unsigned char,unsigned char*) ;scalar_t__ atx_idx; int /*<<< orphan*/  most_iface; } ;

/* Variables and functions */
 struct dim2_hdm* iface_to_hdm (struct most_interface*) ; 
 struct mbo* most_get_mbo (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  most_submit_mbo (struct mbo*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void request_netinfo(struct most_interface *most_iface, int ch_idx,
			    void (*on_netinfo)(struct most_interface *,
					       unsigned char, unsigned char *))
{
	struct dim2_hdm *dev = iface_to_hdm(most_iface);
	struct mbo *mbo;
	u8 *data;

	dev->on_netinfo = on_netinfo;
	if (!on_netinfo)
		return;

	if (dev->atx_idx < 0) {
		pr_err("Async Tx Not initialized\n");
		return;
	}

	mbo = most_get_mbo(&dev->most_iface, dev->atx_idx, NULL);
	if (!mbo)
		return;

	mbo->buffer_length = 5;

	data = mbo->virt_address;

	data[0] = 0x00; /* PML High byte */
	data[1] = 0x03; /* PML Low byte */
	data[2] = 0x02; /* PMHL */
	data[3] = 0x08; /* FPH */
	data[4] = 0x40; /* FMF (FIFO cmd msg - Triggers NAOverMDP) */

	most_submit_mbo(mbo);
}