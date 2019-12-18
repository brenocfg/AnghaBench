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
struct tls_sw_context_rx {char control; } ;
struct tls_prot_info {scalar_t__ version; int prepend_size; } ;
struct strp_msg {int full_len; int offset; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 scalar_t__ TLS_1_3_VERSION ; 
 int skb_copy_bits (struct sk_buff*,int,char*,int) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 

__attribute__((used)) static int padding_length(struct tls_sw_context_rx *ctx,
			  struct tls_prot_info *prot, struct sk_buff *skb)
{
	struct strp_msg *rxm = strp_msg(skb);
	int sub = 0;

	/* Determine zero-padding length */
	if (prot->version == TLS_1_3_VERSION) {
		char content_type = 0;
		int err;
		int back = 17;

		while (content_type == 0) {
			if (back > rxm->full_len - prot->prepend_size)
				return -EBADMSG;
			err = skb_copy_bits(skb,
					    rxm->offset + rxm->full_len - back,
					    &content_type, 1);
			if (err)
				return err;
			if (content_type)
				break;
			sub++;
			back++;
		}
		ctx->control = content_type;
	}
	return sub;
}