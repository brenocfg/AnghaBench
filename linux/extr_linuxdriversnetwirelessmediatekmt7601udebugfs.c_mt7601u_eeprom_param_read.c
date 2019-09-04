#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tssi_data {int /*<<< orphan*/  tx0_delta_offset; int /*<<< orphan*/ * offset; int /*<<< orphan*/  slope; } ;
struct seq_file {struct mt7601u_dev* private; } ;
struct mt7601u_rate_power {TYPE_4__* ht; TYPE_3__* ofdm; TYPE_2__* cck; } ;
struct mt7601u_dev {TYPE_5__* ee; } ;
struct TYPE_6__ {scalar_t__ num; scalar_t__ start; } ;
struct TYPE_10__ {int /*<<< orphan*/  tssi_enabled; int /*<<< orphan*/ * chan_pwr; TYPE_1__ reg; int /*<<< orphan*/  lna_gain; int /*<<< orphan*/  ref_temp; int /*<<< orphan*/ * rssi_offset; int /*<<< orphan*/  rf_freq_off; struct tssi_data tssi_data; struct mt7601u_rate_power power_rate_table; } ;
struct TYPE_9__ {int /*<<< orphan*/  bw40; int /*<<< orphan*/  bw20; int /*<<< orphan*/  raw; } ;
struct TYPE_8__ {int /*<<< orphan*/  bw40; int /*<<< orphan*/  bw20; int /*<<< orphan*/  raw; } ;
struct TYPE_7__ {int /*<<< orphan*/  bw40; int /*<<< orphan*/  bw20; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int
mt7601u_eeprom_param_read(struct seq_file *file, void *data)
{
	struct mt7601u_dev *dev = file->private;
	struct mt7601u_rate_power *rp = &dev->ee->power_rate_table;
	struct tssi_data *td = &dev->ee->tssi_data;
	int i;

	seq_printf(file, "RF freq offset: %hhx\n", dev->ee->rf_freq_off);
	seq_printf(file, "RSSI offset: %hhx %hhx\n",
		   dev->ee->rssi_offset[0], dev->ee->rssi_offset[1]);
	seq_printf(file, "Reference temp: %hhx\n", dev->ee->ref_temp);
	seq_printf(file, "LNA gain: %hhx\n", dev->ee->lna_gain);
	seq_printf(file, "Reg channels: %hhu-%hhu\n", dev->ee->reg.start,
		   dev->ee->reg.start + dev->ee->reg.num - 1);

	seq_puts(file, "Per rate power:\n");
	for (i = 0; i < 2; i++)
		seq_printf(file, "\t raw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   rp->cck[i].raw, rp->cck[i].bw20, rp->cck[i].bw40);
	for (i = 0; i < 4; i++)
		seq_printf(file, "\t raw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   rp->ofdm[i].raw, rp->ofdm[i].bw20, rp->ofdm[i].bw40);
	for (i = 0; i < 4; i++)
		seq_printf(file, "\t raw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   rp->ht[i].raw, rp->ht[i].bw20, rp->ht[i].bw40);

	seq_puts(file, "Per channel power:\n");
	for (i = 0; i < 7; i++)
		seq_printf(file, "\t tx_power  ch%u:%02hhx ch%u:%02hhx\n",
			   i * 2 + 1, dev->ee->chan_pwr[i * 2],
			   i * 2 + 2, dev->ee->chan_pwr[i * 2 + 1]);

	if (!dev->ee->tssi_enabled)
		return 0;

	seq_puts(file, "TSSI:\n");
	seq_printf(file, "\t slope:%02hhx\n", td->slope);
	seq_printf(file, "\t offset=%02hhx %02hhx %02hhx\n",
		   td->offset[0], td->offset[1], td->offset[2]);
	seq_printf(file, "\t delta_off:%08x\n", td->tx0_delta_offset);

	return 0;
}