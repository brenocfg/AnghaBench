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
struct usb_cdc_ncm_nth16 {void* wNdpIndex; } ;
struct usb_cdc_ncm_ndp16 {scalar_t__ dwSignature; void* wLength; void* wNextNdpIndex; } ;
struct usb_cdc_ncm_dpe16 {int dummy; } ;
struct sk_buff {size_t len; scalar_t__ data; } ;
struct cdc_ncm_ctx {int drvflags; size_t tx_curr_size; size_t max_ndp_size; struct usb_cdc_ncm_ndp16* delayed_ndp16; int /*<<< orphan*/  tx_ndp_modulus; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int CDC_NCM_FLAG_NDP_TO_END ; 
 int /*<<< orphan*/  cdc_ncm_align_tail (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 void* cpu_to_le16 (int) ; 
 size_t le16_to_cpu (void*) ; 
 struct usb_cdc_ncm_ndp16* skb_put_zero (struct sk_buff*,size_t) ; 

__attribute__((used)) static struct usb_cdc_ncm_ndp16 *cdc_ncm_ndp(struct cdc_ncm_ctx *ctx, struct sk_buff *skb, __le32 sign, size_t reserve)
{
	struct usb_cdc_ncm_ndp16 *ndp16 = NULL;
	struct usb_cdc_ncm_nth16 *nth16 = (void *)skb->data;
	size_t ndpoffset = le16_to_cpu(nth16->wNdpIndex);

	/* If NDP should be moved to the end of the NCM package, we can't follow the
	* NTH16 header as we would normally do. NDP isn't written to the SKB yet, and
	* the wNdpIndex field in the header is actually not consistent with reality. It will be later.
	*/
	if (ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END) {
		if (ctx->delayed_ndp16->dwSignature == sign)
			return ctx->delayed_ndp16;

		/* We can only push a single NDP to the end. Return
		 * NULL to send what we've already got and queue this
		 * skb for later.
		 */
		else if (ctx->delayed_ndp16->dwSignature)
			return NULL;
	}

	/* follow the chain of NDPs, looking for a match */
	while (ndpoffset) {
		ndp16 = (struct usb_cdc_ncm_ndp16 *)(skb->data + ndpoffset);
		if  (ndp16->dwSignature == sign)
			return ndp16;
		ndpoffset = le16_to_cpu(ndp16->wNextNdpIndex);
	}

	/* align new NDP */
	if (!(ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END))
		cdc_ncm_align_tail(skb, ctx->tx_ndp_modulus, 0, ctx->tx_curr_size);

	/* verify that there is room for the NDP and the datagram (reserve) */
	if ((ctx->tx_curr_size - skb->len - reserve) < ctx->max_ndp_size)
		return NULL;

	/* link to it */
	if (ndp16)
		ndp16->wNextNdpIndex = cpu_to_le16(skb->len);
	else
		nth16->wNdpIndex = cpu_to_le16(skb->len);

	/* push a new empty NDP */
	if (!(ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END))
		ndp16 = skb_put_zero(skb, ctx->max_ndp_size);
	else
		ndp16 = ctx->delayed_ndp16;

	ndp16->dwSignature = sign;
	ndp16->wLength = cpu_to_le16(sizeof(struct usb_cdc_ncm_ndp16) + sizeof(struct usb_cdc_ncm_dpe16));
	return ndp16;
}