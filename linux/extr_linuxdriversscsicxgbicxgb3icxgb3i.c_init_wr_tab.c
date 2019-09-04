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

/* Variables and functions */
 int SKB_WR_LIST_SIZE ; 
 int* skb_wrs ; 
 unsigned int wrlen ; 

__attribute__((used)) static void init_wr_tab(unsigned int wr_len)
{
	int i;

	if (skb_wrs[1])		/* already initialized */
		return;
	for (i = 1; i < SKB_WR_LIST_SIZE; i++) {
		int sgl_len = (3 * i) / 2 + (i & 1);

		sgl_len += 3;
		skb_wrs[i] = (sgl_len <= wr_len
			      ? 1 : 1 + (sgl_len - 2) / (wr_len - 1));
	}
	wrlen = wr_len * 8;
}