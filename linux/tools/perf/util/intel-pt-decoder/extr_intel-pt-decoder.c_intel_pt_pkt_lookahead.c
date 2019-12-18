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
struct TYPE_2__ {scalar_t__ type; } ;
struct intel_pt_pkt_info {size_t pos; size_t pkt_len; scalar_t__ last_packet_type; TYPE_1__ packet; void* data; struct intel_pt_decoder* decoder; } ;
struct intel_pt_decoder {unsigned char* buf; int pkt_ctx; size_t len; size_t pos; size_t pkt_step; scalar_t__ last_packet_type; } ;
typedef  int (* intel_pt_pkt_cb_t ) (struct intel_pt_pkt_info*) ;
typedef  enum intel_pt_pkt_ctx { ____Placeholder_intel_pt_pkt_ctx } intel_pt_pkt_ctx ;

/* Variables and functions */
 int INTEL_PT_NEED_MORE_BYTES ; 
 scalar_t__ INTEL_PT_PAD ; 
 int intel_pt_get_packet (unsigned char const*,size_t,TYPE_1__*,int*) ; 

__attribute__((used)) static int intel_pt_pkt_lookahead(struct intel_pt_decoder *decoder,
				  intel_pt_pkt_cb_t cb, void *data)
{
	struct intel_pt_pkt_info pkt_info;
	const unsigned char *buf = decoder->buf;
	enum intel_pt_pkt_ctx pkt_ctx = decoder->pkt_ctx;
	size_t len = decoder->len;
	int ret;

	pkt_info.decoder          = decoder;
	pkt_info.pos              = decoder->pos;
	pkt_info.pkt_len          = decoder->pkt_step;
	pkt_info.last_packet_type = decoder->last_packet_type;
	pkt_info.data             = data;

	while (1) {
		do {
			pkt_info.pos += pkt_info.pkt_len;
			buf          += pkt_info.pkt_len;
			len          -= pkt_info.pkt_len;

			if (!len)
				return INTEL_PT_NEED_MORE_BYTES;

			ret = intel_pt_get_packet(buf, len, &pkt_info.packet,
						  &pkt_ctx);
			if (!ret)
				return INTEL_PT_NEED_MORE_BYTES;
			if (ret < 0)
				return ret;

			pkt_info.pkt_len = ret;
		} while (pkt_info.packet.type == INTEL_PT_PAD);

		ret = cb(&pkt_info);
		if (ret)
			return 0;

		pkt_info.last_packet_type = pkt_info.packet.type;
	}
}