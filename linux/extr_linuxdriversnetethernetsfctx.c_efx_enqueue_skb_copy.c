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
struct sk_buff {unsigned int len; } ;
struct efx_tx_queue {int /*<<< orphan*/  insert_count; } ;
struct efx_tx_buffer {unsigned int len; int /*<<< orphan*/  flags; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_TX_BUF_SKB ; 
 unsigned int EFX_TX_CB_SIZE ; 
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 
 int /*<<< orphan*/  EFX_WARN_ON_PARANOID (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * efx_tx_get_copy_buffer (struct efx_tx_queue*,struct efx_tx_buffer*) ; 
 struct efx_tx_buffer* efx_tx_queue_get_insert_buffer (struct efx_tx_queue*) ; 
 int skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int efx_enqueue_skb_copy(struct efx_tx_queue *tx_queue,
				struct sk_buff *skb)
{
	unsigned int copy_len = skb->len;
	struct efx_tx_buffer *buffer;
	u8 *copy_buffer;
	int rc;

	EFX_WARN_ON_ONCE_PARANOID(copy_len > EFX_TX_CB_SIZE);

	buffer = efx_tx_queue_get_insert_buffer(tx_queue);

	copy_buffer = efx_tx_get_copy_buffer(tx_queue, buffer);
	if (unlikely(!copy_buffer))
		return -ENOMEM;

	rc = skb_copy_bits(skb, 0, copy_buffer, copy_len);
	EFX_WARN_ON_PARANOID(rc);
	buffer->len = copy_len;

	buffer->skb = skb;
	buffer->flags = EFX_TX_BUF_SKB;

	++tx_queue->insert_count;
	return rc;
}