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
struct mtk_btcvsd_snd_time_buffer_info {int /*<<< orphan*/  data_count_equi_time; int /*<<< orphan*/  time_stamp_us; } ;
struct mtk_btcvsd_snd {TYPE_1__* tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf_data_equivalent_time; int /*<<< orphan*/  time_stamp; } ;

/* Variables and functions */

__attribute__((used)) static void get_tx_time_stamp(struct mtk_btcvsd_snd *bt,
			      struct mtk_btcvsd_snd_time_buffer_info *ts)
{
	ts->time_stamp_us = bt->tx->time_stamp;
	ts->data_count_equi_time = bt->tx->buf_data_equivalent_time;
}