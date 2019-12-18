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
struct tls_context {int dummy; } ;
struct sk_buff {void* data; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int TLS_CIPHER_AES_GCM_128_TAG_SIZE ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,void*,int) ; 

__attribute__((used)) static void fill_sg_out(struct scatterlist sg_out[3], void *buf,
			struct tls_context *tls_ctx,
			struct sk_buff *nskb,
			int tcp_payload_offset,
			int payload_len,
			int sync_size,
			void *dummy_buf)
{
	sg_set_buf(&sg_out[0], dummy_buf, sync_size);
	sg_set_buf(&sg_out[1], nskb->data + tcp_payload_offset, payload_len);
	/* Add room for authentication tag produced by crypto */
	dummy_buf += sync_size;
	sg_set_buf(&sg_out[2], dummy_buf, TLS_CIPHER_AES_GCM_128_TAG_SIZE);
}