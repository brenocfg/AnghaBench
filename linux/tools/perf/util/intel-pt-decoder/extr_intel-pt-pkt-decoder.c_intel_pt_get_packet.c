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
struct intel_pt_pkt {int dummy; } ;
typedef  enum intel_pt_pkt_ctx { ____Placeholder_intel_pt_pkt_ctx } intel_pt_pkt_ctx ;

/* Variables and functions */
 int intel_pt_do_get_packet (unsigned char const*,size_t,struct intel_pt_pkt*,int) ; 
 int /*<<< orphan*/  intel_pt_upd_pkt_ctx (struct intel_pt_pkt*,int*) ; 

int intel_pt_get_packet(const unsigned char *buf, size_t len,
			struct intel_pt_pkt *packet, enum intel_pt_pkt_ctx *ctx)
{
	int ret;

	ret = intel_pt_do_get_packet(buf, len, packet, *ctx);
	if (ret > 0) {
		while (ret < 8 && len > (size_t)ret && !buf[ret])
			ret += 1;
		intel_pt_upd_pkt_ctx(packet, ctx);
	}
	return ret;
}