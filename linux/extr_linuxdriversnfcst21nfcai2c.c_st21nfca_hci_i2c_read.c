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
typedef  int u8 ;
struct st21nfca_i2c_phy {int current_read_len; int /*<<< orphan*/  phy_lock; struct i2c_client* i2c_dev; } ;
struct sk_buff {scalar_t__* data; int len; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EAGAIN ; 
 int EIO ; 
 int EREMOTEIO ; 
 scalar_t__ IS_START_OF_FRAME (int*) ; 
 int ST21NFCA_HCI_LLC_MAX_PAYLOAD ; 
 scalar_t__ ST21NFCA_SOF_EOF ; 
 int i2c_master_recv (struct i2c_client*,int*,int) ; 
 int* len_seq ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int st21nfca_hci_i2c_repack (struct sk_buff*) ; 
 int* wait_tab ; 

__attribute__((used)) static int st21nfca_hci_i2c_read(struct st21nfca_i2c_phy *phy,
				 struct sk_buff *skb)
{
	int r, i;
	u8 len;
	u8 buf[ST21NFCA_HCI_LLC_MAX_PAYLOAD];
	struct i2c_client *client = phy->i2c_dev;

	if (phy->current_read_len < ARRAY_SIZE(len_seq)) {
		len = len_seq[phy->current_read_len];

		/*
		 * Add retry mecanism
		 * Operation on I2C interface may fail in case of operation on
		 * RF or SWP interface
		 */
		r = 0;
		mutex_lock(&phy->phy_lock);
		for (i = 0; i < ARRAY_SIZE(wait_tab) && r <= 0; i++) {
			r = i2c_master_recv(client, buf, len);
			if (r < 0)
				msleep(wait_tab[i]);
		}
		mutex_unlock(&phy->phy_lock);

		if (r != len) {
			phy->current_read_len = 0;
			return -EREMOTEIO;
		}

		/*
		 * The first read sequence does not start with SOF.
		 * Data is corrupeted so we drop it.
		 */
		if (!phy->current_read_len && !IS_START_OF_FRAME(buf)) {
			skb_trim(skb, 0);
			phy->current_read_len = 0;
			return -EIO;
		} else if (phy->current_read_len && IS_START_OF_FRAME(buf)) {
			/*
			 * Previous frame transmission was interrupted and
			 * the frame got repeated.
			 * Received frame start with ST21NFCA_SOF_EOF + 00.
			 */
			skb_trim(skb, 0);
			phy->current_read_len = 0;
		}

		skb_put_data(skb, buf, len);

		if (skb->data[skb->len - 1] == ST21NFCA_SOF_EOF) {
			phy->current_read_len = 0;
			return st21nfca_hci_i2c_repack(skb);
		}
		phy->current_read_len++;
		return -EAGAIN;
	}
	return -EIO;
}