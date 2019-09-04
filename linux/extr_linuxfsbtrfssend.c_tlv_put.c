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
typedef  int u16 ;
struct send_ctx {int send_max_size; int send_size; int send_buf; } ;
struct btrfs_tlv_header {void* tlv_len; void* tlv_type; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_tlv_header*,void const*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tlv_put(struct send_ctx *sctx, u16 attr, const void *data, int len)
{
	struct btrfs_tlv_header *hdr;
	int total_len = sizeof(*hdr) + len;
	int left = sctx->send_max_size - sctx->send_size;

	if (unlikely(left < total_len))
		return -EOVERFLOW;

	hdr = (struct btrfs_tlv_header *) (sctx->send_buf + sctx->send_size);
	hdr->tlv_type = cpu_to_le16(attr);
	hdr->tlv_len = cpu_to_le16(len);
	memcpy(hdr + 1, data, len);
	sctx->send_size += total_len;

	return 0;
}