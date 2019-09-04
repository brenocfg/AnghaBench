#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * tx_buf_list; int /*<<< orphan*/ * rx_buf_list; int /*<<< orphan*/ * buffer_list; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */

__attribute__((used)) static void free_dma_bufs(SLMP_INFO *info)
{
	info->buffer_list = NULL;
	info->rx_buf_list = NULL;
	info->tx_buf_list = NULL;
}