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
typedef  unsigned int u8 ;
struct sst_enum {unsigned int reg; unsigned int tx; int max; int /*<<< orphan*/ * texts; } ;
struct sst_data {int /*<<< orphan*/  lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sst_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int sst_check_and_send_slot_map (struct sst_data*,struct snd_kcontrol*) ; 
 unsigned int* sst_ssp_rx_map ; 
 unsigned int* sst_ssp_tx_map ; 

__attribute__((used)) static int sst_slot_put(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	struct sst_data *drv = snd_soc_component_get_drvdata(c);
	struct sst_enum *e = (void *)kcontrol->private_value;
	int i, ret = 0;
	unsigned int ctl_no = e->reg;
	unsigned int is_tx = e->tx;
	unsigned int slot_channel_no;
	unsigned int val, mux;
	u8 *map;

	map = is_tx ? sst_ssp_rx_map : sst_ssp_tx_map;

	val = 1 << ctl_no;
	mux = ucontrol->value.enumerated.item[0];
	if (mux > e->max - 1)
		return -EINVAL;

	mutex_lock(&drv->lock);
	/* first clear all registers of this bit */
	for (i = 0; i < e->max; i++)
		map[i] &= ~val;

	if (mux == 0) {
		/* kctl set to 'none' and we reset the bits so send IPC */
		ret = sst_check_and_send_slot_map(drv, kcontrol);

		mutex_unlock(&drv->lock);
		return ret;
	}

	/* offset by one to take "None" into account */
	slot_channel_no = mux - 1;
	map[slot_channel_no] |= val;

	dev_dbg(c->dev, "%s %s map = %#x\n",
			is_tx ? "tx channel" : "rx slot",
			e->texts[mux], map[slot_channel_no]);

	ret = sst_check_and_send_slot_map(drv, kcontrol);

	mutex_unlock(&drv->lock);
	return ret;
}