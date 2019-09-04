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
struct wl1251 {struct sk_buff** tx_frames; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int FW_TX_CMPLT_BLOCK_SIZE ; 

__attribute__((used)) static int wl1251_tx_id(struct wl1251 *wl, struct sk_buff *skb)
{
	int i;

	for (i = 0; i < FW_TX_CMPLT_BLOCK_SIZE; i++)
		if (wl->tx_frames[i] == NULL) {
			wl->tx_frames[i] = skb;
			return i;
		}

	return -EBUSY;
}