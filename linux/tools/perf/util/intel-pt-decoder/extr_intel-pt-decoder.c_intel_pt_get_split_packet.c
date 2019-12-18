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
struct intel_pt_decoder {unsigned char* temp_buf; size_t len; unsigned char* buf; size_t pos; unsigned char* next_buf; size_t next_len; int /*<<< orphan*/  pkt_ctx; int /*<<< orphan*/  packet; int /*<<< orphan*/  prev_pkt_ctx; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t INTEL_PT_PKT_MAX_SZ ; 
 int intel_pt_bad_packet (struct intel_pt_decoder*) ; 
 int intel_pt_get_data (struct intel_pt_decoder*,int) ; 
 int intel_pt_get_packet (unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int intel_pt_get_split_packet(struct intel_pt_decoder *decoder)
{
	unsigned char *buf = decoder->temp_buf;
	size_t old_len, len, n;
	int ret;

	old_len = decoder->len;
	len = decoder->len;
	memcpy(buf, decoder->buf, len);

	ret = intel_pt_get_data(decoder, false);
	if (ret) {
		decoder->pos += old_len;
		return ret < 0 ? ret : -EINVAL;
	}

	n = INTEL_PT_PKT_MAX_SZ - len;
	if (n > decoder->len)
		n = decoder->len;
	memcpy(buf + len, decoder->buf, n);
	len += n;

	decoder->prev_pkt_ctx = decoder->pkt_ctx;
	ret = intel_pt_get_packet(buf, len, &decoder->packet, &decoder->pkt_ctx);
	if (ret < (int)old_len) {
		decoder->next_buf = decoder->buf;
		decoder->next_len = decoder->len;
		decoder->buf = buf;
		decoder->len = old_len;
		return intel_pt_bad_packet(decoder);
	}

	decoder->next_buf = decoder->buf + (ret - old_len);
	decoder->next_len = decoder->len - (ret - old_len);

	decoder->buf = buf;
	decoder->len = ret;

	return ret;
}