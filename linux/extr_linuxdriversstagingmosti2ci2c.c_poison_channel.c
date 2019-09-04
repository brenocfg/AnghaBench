#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct most_interface {int dummy; } ;
struct mbo {int /*<<< orphan*/  (* complete ) (struct mbo*) ;int /*<<< orphan*/  status; scalar_t__ processed_length; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  dwork; } ;
struct hdm_i2c {TYPE_2__ rx; TYPE_1__* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CH_RX ; 
 int /*<<< orphan*/  MBO_E_CLOSE ; 
 int NUM_CHANNELS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hdm_i2c*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct mbo* list_first_mbo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  polling_rate ; 
 int /*<<< orphan*/  stub1 (struct mbo*) ; 
 struct hdm_i2c* to_hdm (struct most_interface*) ; 

__attribute__((used)) static int poison_channel(struct most_interface *most_iface,
			  int ch_idx)
{
	struct hdm_i2c *dev = to_hdm(most_iface);
	struct mbo *mbo;

	BUG_ON(ch_idx < 0 || ch_idx >= NUM_CHANNELS);

	if (ch_idx == CH_RX) {
		if (!polling_rate)
			free_irq(dev->client->irq, dev);
		cancel_delayed_work_sync(&dev->rx.dwork);

		while (!list_empty(&dev->rx.list)) {
			mbo = list_first_mbo(&dev->rx.list);
			list_del(&mbo->list);

			mbo->processed_length = 0;
			mbo->status = MBO_E_CLOSE;
			mbo->complete(mbo);
		}
	}

	return 0;
}