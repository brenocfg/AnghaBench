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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ tx_buff_size; scalar_t__ tx_buff_pos; } ;
struct atmel_private {scalar_t__ tx_buff_tail; int tx_desc_free; scalar_t__ tx_free_mem; TYPE_1__ host_info; } ;

/* Variables and functions */

__attribute__((used)) static u16 find_tx_buff(struct atmel_private *priv, u16 len)
{
	u16 bottom_free = priv->host_info.tx_buff_size - priv->tx_buff_tail;

	if (priv->tx_desc_free == 3 || priv->tx_free_mem < len)
		return 0;

	if (bottom_free >= len)
		return priv->host_info.tx_buff_pos + priv->tx_buff_tail;

	if (priv->tx_free_mem - bottom_free >= len) {
		priv->tx_buff_tail = 0;
		return priv->host_info.tx_buff_pos;
	}

	return 0;
}