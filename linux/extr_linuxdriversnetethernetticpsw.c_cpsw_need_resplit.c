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
struct cpsw_common {int speed; int tx_ch_num; TYPE_1__* txv; } ;
struct TYPE_2__ {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int cpdma_chan_get_rate (int /*<<< orphan*/ ) ; 
 int cpsw_get_common_speed (struct cpsw_common*) ; 

__attribute__((used)) static int cpsw_need_resplit(struct cpsw_common *cpsw)
{
	int i, rlim_ch_num;
	int speed, ch_rate;

	/* re-split resources only in case speed was changed */
	speed = cpsw_get_common_speed(cpsw);
	if (speed == cpsw->speed || !speed)
		return 0;

	cpsw->speed = speed;

	for (i = 0, rlim_ch_num = 0; i < cpsw->tx_ch_num; i++) {
		ch_rate = cpdma_chan_get_rate(cpsw->txv[i].ch);
		if (!ch_rate)
			break;

		rlim_ch_num++;
	}

	/* cases not dependent on speed */
	if (!rlim_ch_num || rlim_ch_num == cpsw->tx_ch_num)
		return 0;

	return 1;
}