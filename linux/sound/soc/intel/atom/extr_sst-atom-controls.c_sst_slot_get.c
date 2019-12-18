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
struct sst_enum {unsigned int reg; unsigned int tx; unsigned int max; int /*<<< orphan*/ * texts; } ;
struct sst_data {int /*<<< orphan*/  lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct sst_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int* sst_ssp_rx_map ; 
 unsigned int* sst_ssp_tx_map ; 

__attribute__((used)) static int sst_slot_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct sst_enum *e = (void *)kcontrol->private_value;
	struct snd_soc_component *c = snd_kcontrol_chip(kcontrol);
	struct sst_data *drv = snd_soc_component_get_drvdata(c);
	unsigned int ctl_no = e->reg;
	unsigned int is_tx = e->tx;
	unsigned int val, mux;
	u8 *map = is_tx ? sst_ssp_rx_map : sst_ssp_tx_map;

	mutex_lock(&drv->lock);
	val = 1 << ctl_no;
	/* search which slot/channel has this bit set - there should be only one */
	for (mux = e->max; mux > 0;  mux--)
		if (map[mux - 1] & val)
			break;

	ucontrol->value.enumerated.item[0] = mux;
	mutex_unlock(&drv->lock);

	dev_dbg(c->dev, "%s - %s map = %#x\n",
			is_tx ? "tx channel" : "rx slot",
			 e->texts[mux], mux ? map[mux - 1] : -1);
	return 0;
}