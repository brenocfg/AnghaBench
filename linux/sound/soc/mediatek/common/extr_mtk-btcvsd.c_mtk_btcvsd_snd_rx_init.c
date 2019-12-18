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
struct mtk_btcvsd_snd {TYPE_1__* rx; TYPE_1__* rx_packet_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  stream; scalar_t__ rw_cnt; scalar_t__ timeout; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  packet_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTCVSD_RX_BUF_SIZE ; 
 int /*<<< orphan*/  BTCVSD_RX_PACKET_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtk_btcvsd_snd_rx_init(struct mtk_btcvsd_snd *bt)
{
	memset(bt->rx, 0, sizeof(*bt->rx));
	memset(bt->rx_packet_buf, 0, sizeof(bt->rx_packet_buf));

	bt->rx->packet_size = BTCVSD_RX_PACKET_SIZE;
	bt->rx->buf_size = BTCVSD_RX_BUF_SIZE;
	bt->rx->timeout = 0;
	bt->rx->rw_cnt = 0;
	bt->rx->stream = SNDRV_PCM_STREAM_CAPTURE;
	return 0;
}