#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ad7280_state {int slave_num; TYPE_2__* iio_attr; } ;
struct TYPE_6__ {int mode; void* name; } ;
struct TYPE_4__ {TYPE_3__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct TYPE_5__ {int address; TYPE_1__ dev_attr; } ;

/* Variables and functions */
 int AD7280A_CB1_TIMER ; 
 int AD7280A_CELLS_PER_DEV ; 
 int AD7280A_CELL_VOLTAGE_1 ; 
 int AD7280A_CELL_VOLTAGE_6 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__** ad7280_attributes ; 
 int /*<<< orphan*/  ad7280_show_balance_sw ; 
 int /*<<< orphan*/  ad7280_show_balance_timer ; 
 int /*<<< orphan*/  ad7280_store_balance_sw ; 
 int /*<<< orphan*/  ad7280_store_balance_timer ; 
 int ad7280a_devaddr (int) ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7280_attr_init(struct ad7280_state *st)
{
	int dev, ch, cnt;

	st->iio_attr = kcalloc(2, sizeof(*st->iio_attr) *
			       (st->slave_num + 1) * AD7280A_CELLS_PER_DEV,
			       GFP_KERNEL);
	if (!st->iio_attr)
		return -ENOMEM;

	for (dev = 0, cnt = 0; dev <= st->slave_num; dev++)
		for (ch = AD7280A_CELL_VOLTAGE_1; ch <= AD7280A_CELL_VOLTAGE_6;
			ch++, cnt++) {
			st->iio_attr[cnt].address =
				ad7280a_devaddr(dev) << 8 | ch;
			st->iio_attr[cnt].dev_attr.attr.mode =
				0644;
			st->iio_attr[cnt].dev_attr.show =
				ad7280_show_balance_sw;
			st->iio_attr[cnt].dev_attr.store =
				ad7280_store_balance_sw;
			st->iio_attr[cnt].dev_attr.attr.name =
				kasprintf(GFP_KERNEL,
					  "in%d-in%d_balance_switch_en",
					  dev * AD7280A_CELLS_PER_DEV + ch,
					  dev * AD7280A_CELLS_PER_DEV + ch + 1);
			ad7280_attributes[cnt] =
				&st->iio_attr[cnt].dev_attr.attr;
			cnt++;
			st->iio_attr[cnt].address =
				ad7280a_devaddr(dev) << 8 |
				(AD7280A_CB1_TIMER + ch);
			st->iio_attr[cnt].dev_attr.attr.mode =
				0644;
			st->iio_attr[cnt].dev_attr.show =
				ad7280_show_balance_timer;
			st->iio_attr[cnt].dev_attr.store =
				ad7280_store_balance_timer;
			st->iio_attr[cnt].dev_attr.attr.name =
				kasprintf(GFP_KERNEL,
					  "in%d-in%d_balance_timer",
					  dev * AD7280A_CELLS_PER_DEV + ch,
					  dev * AD7280A_CELLS_PER_DEV + ch + 1);
			ad7280_attributes[cnt] =
				&st->iio_attr[cnt].dev_attr.attr;
		}

	ad7280_attributes[cnt] = NULL;

	return 0;
}