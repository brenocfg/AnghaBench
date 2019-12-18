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
struct sprd_mcdt_dev {struct sprd_mcdt_chan* chan; } ;
struct sprd_mcdt_chan {int id; int /*<<< orphan*/  list; struct sprd_mcdt_dev* mcdt; scalar_t__ fifo_phys; int /*<<< orphan*/  type; } ;
struct resource {scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MCDT_ADC_CHANNEL_NUM ; 
 scalar_t__ MCDT_CH0_RXD ; 
 scalar_t__ MCDT_CH0_TXD ; 
 int MCDT_CHANNEL_NUM ; 
 int /*<<< orphan*/  SPRD_MCDT_ADC_CHAN ; 
 int /*<<< orphan*/  SPRD_MCDT_DAC_CHAN ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_mcdt_chan_list ; 
 int /*<<< orphan*/  sprd_mcdt_list_mutex ; 

__attribute__((used)) static void sprd_mcdt_init_chans(struct sprd_mcdt_dev *mcdt,
				 struct resource *res)
{
	int i;

	for (i = 0; i < MCDT_CHANNEL_NUM; i++) {
		struct sprd_mcdt_chan *chan = &mcdt->chan[i];

		if (i < MCDT_ADC_CHANNEL_NUM) {
			chan->id = i;
			chan->type = SPRD_MCDT_ADC_CHAN;
			chan->fifo_phys = res->start + MCDT_CH0_RXD + i * 4;
		} else {
			chan->id = i - MCDT_ADC_CHANNEL_NUM;
			chan->type = SPRD_MCDT_DAC_CHAN;
			chan->fifo_phys = res->start + MCDT_CH0_TXD +
				(i - MCDT_ADC_CHANNEL_NUM) * 4;
		}

		chan->mcdt = mcdt;
		INIT_LIST_HEAD(&chan->list);

		mutex_lock(&sprd_mcdt_list_mutex);
		list_add_tail(&chan->list, &sprd_mcdt_chan_list);
		mutex_unlock(&sprd_mcdt_list_mutex);
	}
}