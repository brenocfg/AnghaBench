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
struct channel_data {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned long MAX_DMA_ADDRESS ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cosa_dma_able(struct channel_data *chan, char *buf, int len)
{
	static int count;
	unsigned long b = (unsigned long)buf;
	if (b+len >= MAX_DMA_ADDRESS)
		return 0;
	if ((b^ (b+len)) & 0x10000) {
		if (count++ < 5)
			pr_info("%s: packet spanning a 64k boundary\n",
				chan->name);
		return 0;
	}
	return 1;
}