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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int bpf_skb_generic_push(struct sk_buff *skb, u32 off, u32 len)
{
	/* Caller already did skb_cow() with len as headroom,
	 * so no need to do it here.
	 */
	skb_push(skb, len);
	memmove(skb->data, skb->data + len, off);
	memset(skb->data + off, 0, len);

	/* No skb_postpush_rcsum(skb, skb->data + off, len)
	 * needed here as it does not change the skb->csum
	 * result for checksum complete when summing over
	 * zeroed blocks.
	 */
	return 0;
}