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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct brcmf_sdio_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  brcmf_err (char*,int /*<<< orphan*/ ) ; 
 int brcmf_sdiod_recv_pkt (struct brcmf_sdio_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 struct sk_buff* brcmu_pkt_buf_get_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int brcmf_sdiod_recv_buf(struct brcmf_sdio_dev *sdiodev, u8 *buf, uint nbytes)
{
	struct sk_buff *mypkt;
	int err;

	mypkt = brcmu_pkt_buf_get_skb(nbytes);
	if (!mypkt) {
		brcmf_err("brcmu_pkt_buf_get_skb failed: len %d\n",
			  nbytes);
		return -EIO;
	}

	err = brcmf_sdiod_recv_pkt(sdiodev, mypkt);
	if (!err)
		memcpy(buf, mypkt->data, nbytes);

	brcmu_pkt_buf_free_skb(mypkt);
	return err;
}