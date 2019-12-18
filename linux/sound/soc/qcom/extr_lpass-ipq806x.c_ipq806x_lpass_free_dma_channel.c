#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpass_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ipq806x_lpass_free_dma_channel(struct lpass_data *drvdata, int chan)
{
	return 0;
}