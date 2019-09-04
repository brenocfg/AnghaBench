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
struct ad7280_state {int slave_num; TYPE_2__* channels; } ;
struct TYPE_3__ {unsigned char sign; int realbits; int storagebits; scalar_t__ shift; } ;
struct TYPE_4__ {int differential; int channel; int channel2; int indexed; int address; int scan_index; TYPE_1__ scan_type; void* type; void* info_mask_shared_by_type; void* info_mask_separate; } ;

/* Variables and functions */
 int AD7280A_ALL_CELLS ; 
 int AD7280A_AUX_ADC_1 ; 
 int AD7280A_AUX_ADC_6 ; 
 int AD7280A_CELL_VOLTAGE_1 ; 
 void* BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_RAW ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_SCALE ; 
 void* IIO_TEMP ; 
 void* IIO_TIMESTAMP ; 
 void* IIO_VOLTAGE ; 
 int ad7280a_devaddr (int) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7280_channel_init(struct ad7280_state *st)
{
	int dev, ch, cnt;

	st->channels = kcalloc((st->slave_num + 1) * 12 + 2,
			       sizeof(*st->channels), GFP_KERNEL);
	if (!st->channels)
		return -ENOMEM;

	for (dev = 0, cnt = 0; dev <= st->slave_num; dev++)
		for (ch = AD7280A_CELL_VOLTAGE_1; ch <= AD7280A_AUX_ADC_6;
			ch++, cnt++) {
			if (ch < AD7280A_AUX_ADC_1) {
				st->channels[cnt].type = IIO_VOLTAGE;
				st->channels[cnt].differential = 1;
				st->channels[cnt].channel = (dev * 6) + ch;
				st->channels[cnt].channel2 =
					st->channels[cnt].channel + 1;
			} else {
				st->channels[cnt].type = IIO_TEMP;
				st->channels[cnt].channel = (dev * 6) + ch - 6;
			}
			st->channels[cnt].indexed = 1;
			st->channels[cnt].info_mask_separate =
				BIT(IIO_CHAN_INFO_RAW);
			st->channels[cnt].info_mask_shared_by_type =
				BIT(IIO_CHAN_INFO_SCALE);
			st->channels[cnt].address =
				ad7280a_devaddr(dev) << 8 | ch;
			st->channels[cnt].scan_index = cnt;
			st->channels[cnt].scan_type.sign = 'u';
			st->channels[cnt].scan_type.realbits = 12;
			st->channels[cnt].scan_type.storagebits = 32;
			st->channels[cnt].scan_type.shift = 0;
		}

	st->channels[cnt].type = IIO_VOLTAGE;
	st->channels[cnt].differential = 1;
	st->channels[cnt].channel = 0;
	st->channels[cnt].channel2 = dev * 6;
	st->channels[cnt].address = AD7280A_ALL_CELLS;
	st->channels[cnt].indexed = 1;
	st->channels[cnt].info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
	st->channels[cnt].info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE);
	st->channels[cnt].scan_index = cnt;
	st->channels[cnt].scan_type.sign = 'u';
	st->channels[cnt].scan_type.realbits = 32;
	st->channels[cnt].scan_type.storagebits = 32;
	st->channels[cnt].scan_type.shift = 0;
	cnt++;
	st->channels[cnt].type = IIO_TIMESTAMP;
	st->channels[cnt].channel = -1;
	st->channels[cnt].scan_index = cnt;
	st->channels[cnt].scan_type.sign = 's';
	st->channels[cnt].scan_type.realbits = 64;
	st->channels[cnt].scan_type.storagebits = 64;
	st->channels[cnt].scan_type.shift = 0;

	return cnt + 1;
}