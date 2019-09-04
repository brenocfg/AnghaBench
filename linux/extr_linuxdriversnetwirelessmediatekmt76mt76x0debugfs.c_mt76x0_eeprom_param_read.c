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
struct seq_file {struct mt76x0_dev* private; } ;
struct mt76x0_dev {TYPE_2__* ee; } ;
struct TYPE_3__ {scalar_t__ num; scalar_t__ start; } ;
struct TYPE_4__ {int* rssi_offset_5ghz; int* lna_gain_5ghz; int* tx_pwr_per_chan; int** tx_pwr_cfg_2g; int** tx_pwr_cfg_5g; TYPE_1__ reg; int /*<<< orphan*/  pa_type; int /*<<< orphan*/  lna_gain_2ghz; int /*<<< orphan*/  temp_off; int /*<<< orphan*/ * rssi_offset_2ghz; int /*<<< orphan*/  rf_freq_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int
mt76x0_eeprom_param_read(struct seq_file *file, void *data)
{
	struct mt76x0_dev *dev = file->private;
	int i;

	seq_printf(file, "RF freq offset: %hhx\n", dev->ee->rf_freq_off);
	seq_printf(file, "RSSI offset 2GHz: %hhx %hhx\n",
		   dev->ee->rssi_offset_2ghz[0], dev->ee->rssi_offset_2ghz[1]);
	seq_printf(file, "RSSI offset 5GHz: %hhx %hhx %hhx\n",
		   dev->ee->rssi_offset_5ghz[0], dev->ee->rssi_offset_5ghz[1],
		   dev->ee->rssi_offset_5ghz[2]);
	seq_printf(file, "Temperature offset: %hhx\n", dev->ee->temp_off);
	seq_printf(file, "LNA gain 2Ghz: %hhx\n", dev->ee->lna_gain_2ghz);
	seq_printf(file, "LNA gain 5Ghz: %hhx %hhx %hhx\n",
		   dev->ee->lna_gain_5ghz[0], dev->ee->lna_gain_5ghz[1],
		   dev->ee->lna_gain_5ghz[2]);
	seq_printf(file, "Power Amplifier type %hhx\n", dev->ee->pa_type);
	seq_printf(file, "Reg channels: %hhu-%hhu\n", dev->ee->reg.start,
		   dev->ee->reg.start + dev->ee->reg.num - 1);

	seq_puts(file, "Per channel power:\n");
	for (i = 0; i < 58; i++)
		seq_printf(file, "\t%d chan:%d pwr:%d\n", i, i,
			   dev->ee->tx_pwr_per_chan[i]);

	seq_puts(file, "Per rate power 2GHz:\n");
	for (i = 0; i < 5; i++)
		seq_printf(file, "\t %d bw20:%d bw40:%d\n",
			   i, dev->ee->tx_pwr_cfg_2g[i][0],
			      dev->ee->tx_pwr_cfg_5g[i][1]);

	seq_puts(file, "Per rate power 5GHz:\n");
	for (i = 0; i < 5; i++)
		seq_printf(file, "\t %d bw20:%d bw40:%d\n",
			   i, dev->ee->tx_pwr_cfg_5g[i][0],
			      dev->ee->tx_pwr_cfg_5g[i][1]);

	return 0;
}