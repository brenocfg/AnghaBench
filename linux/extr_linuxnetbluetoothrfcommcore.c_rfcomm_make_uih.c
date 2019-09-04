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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; } ;
struct rfcomm_hdr {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  addr; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  RFCOMM_UIH ; 
 int /*<<< orphan*/  __ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __fcs (void*) ; 
 int /*<<< orphan*/  __len16 (int) ; 
 scalar_t__ __len8 (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rfcomm_hdr* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void rfcomm_make_uih(struct sk_buff *skb, u8 addr)
{
	struct rfcomm_hdr *hdr;
	int len = skb->len;
	u8 *crc;

	if (len > 127) {
		hdr = skb_push(skb, 4);
		put_unaligned(cpu_to_le16(__len16(len)), (__le16 *) &hdr->len);
	} else {
		hdr = skb_push(skb, 3);
		hdr->len = __len8(len);
	}
	hdr->addr = addr;
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);

	crc = skb_put(skb, 1);
	*crc = __fcs((void *) hdr);
}