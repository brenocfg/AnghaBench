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
typedef  unsigned int u32 ;
struct usbnet {int dummy; } ;
struct sk_buff {scalar_t__ ip_summed; int len; scalar_t__ data; scalar_t__ csum_offset; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __sum16 ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 unsigned int SMSC95XX_TX_OVERHEAD ; 
 unsigned int SMSC95XX_TX_OVERHEAD_CSUM ; 
 unsigned int TX_CMD_A_FIRST_SEG_ ; 
 unsigned int TX_CMD_A_LAST_SEG_ ; 
 unsigned int TX_CMD_B_CSUM_ENABLE ; 
 int /*<<< orphan*/  cpu_to_le32s (unsigned int*) ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned int*,int) ; 
 long skb_checksum_start_offset (struct sk_buff*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 unsigned int smsc95xx_calc_csum_preamble (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *smsc95xx_tx_fixup(struct usbnet *dev,
					 struct sk_buff *skb, gfp_t flags)
{
	bool csum = skb->ip_summed == CHECKSUM_PARTIAL;
	unsigned int align_bytes = -((uintptr_t)skb->data) & 0x3;
	int overhead = csum ? SMSC95XX_TX_OVERHEAD_CSUM + align_bytes
				: SMSC95XX_TX_OVERHEAD + align_bytes;
	u32 tx_cmd_a, tx_cmd_b;

	/* We do not advertise SG, so skbs should be already linearized */
	BUG_ON(skb_shinfo(skb)->nr_frags);

	/* Make writable and expand header space by overhead if required */
	if (skb_cow_head(skb, overhead)) {
		/* Must deallocate here as returning NULL to indicate error
		 * means the skb won't be deallocated in the caller.
		 */
		dev_kfree_skb_any(skb);
		return NULL;
	}

	if (csum) {
		if (skb->len <= 45) {
			/* workaround - hardware tx checksum does not work
			 * properly with extremely small packets */
			long csstart = skb_checksum_start_offset(skb);
			__wsum calc = csum_partial(skb->data + csstart,
				skb->len - csstart, 0);
			*((__sum16 *)(skb->data + csstart
				+ skb->csum_offset)) = csum_fold(calc);

			csum = false;
		} else {
			u32 csum_preamble = smsc95xx_calc_csum_preamble(skb);
			skb_push(skb, 4);
			cpu_to_le32s(&csum_preamble);
			memcpy(skb->data, &csum_preamble, 4);
		}
	}

	skb_push(skb, 4 + align_bytes);
	tx_cmd_b = (u32)(skb->len - 4 - align_bytes);
	if (csum)
		tx_cmd_b |= TX_CMD_B_CSUM_ENABLE;
	cpu_to_le32s(&tx_cmd_b);
	memcpy(skb->data, &tx_cmd_b, 4);

	skb_push(skb, 4);
	tx_cmd_a = (u32)(skb->len - 8 - align_bytes) | TX_CMD_A_FIRST_SEG_ |
		(align_bytes << 16) | TX_CMD_A_LAST_SEG_;
	cpu_to_le32s(&tx_cmd_a);
	memcpy(skb->data, &tx_cmd_a, 4);

	return skb;
}