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
struct TYPE_6__ {TYPE_2__* chan; } ;
struct mt7601u_dev {TYPE_3__ chandef; TYPE_1__* ee; } ;
struct TYPE_5__ {int hw_value; } ;
struct TYPE_4__ {int* chan_pwr; } ;

/* Variables and functions */

__attribute__((used)) static int mt7601u_current_tx_power(struct mt7601u_dev *dev)
{
	return dev->ee->chan_pwr[dev->chandef.chan->hw_value - 1];
}