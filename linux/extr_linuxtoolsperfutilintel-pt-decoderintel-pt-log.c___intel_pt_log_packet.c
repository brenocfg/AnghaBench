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
typedef  int /*<<< orphan*/  uint64_t ;
struct intel_pt_pkt {int dummy; } ;

/* Variables and functions */
 int INTEL_PT_PKT_DESC_MAX ; 
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ intel_pt_log_open () ; 
 int /*<<< orphan*/  intel_pt_pkt_desc (struct intel_pt_pkt const*,char*,int) ; 
 int /*<<< orphan*/  intel_pt_print_data (unsigned char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __intel_pt_log_packet(const struct intel_pt_pkt *packet, int pkt_len,
			   uint64_t pos, const unsigned char *buf)
{
	char desc[INTEL_PT_PKT_DESC_MAX];

	if (intel_pt_log_open())
		return;

	intel_pt_print_data(buf, pkt_len, pos, 0);
	intel_pt_pkt_desc(packet, desc, INTEL_PT_PKT_DESC_MAX);
	fprintf(f, "%s\n", desc);
}