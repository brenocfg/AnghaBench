#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int /*<<< orphan*/  private; } ;
struct TYPE_2__ {int /*<<< orphan*/  vht; int /*<<< orphan*/  ht; int /*<<< orphan*/  ofdm; int /*<<< orphan*/  cck; } ;
struct mt76x2_dev {TYPE_1__ rate_power; int /*<<< orphan*/  target_power_delta; int /*<<< orphan*/  target_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct mt76x2_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts_array (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_txpower(struct seq_file *file, void *data)
{
	struct mt76x2_dev *dev = dev_get_drvdata(file->private);

	seq_printf(file, "Target power: %d\n", dev->target_power);

	seq_puts_array(file, "Delta", dev->target_power_delta,
		       ARRAY_SIZE(dev->target_power_delta));
	seq_puts_array(file, "CCK", dev->rate_power.cck,
		       ARRAY_SIZE(dev->rate_power.cck));
	seq_puts_array(file, "OFDM", dev->rate_power.ofdm,
		       ARRAY_SIZE(dev->rate_power.ofdm));
	seq_puts_array(file, "HT", dev->rate_power.ht,
		       ARRAY_SIZE(dev->rate_power.ht));
	seq_puts_array(file, "VHT", dev->rate_power.vht,
		       ARRAY_SIZE(dev->rate_power.vht));
	return 0;
}