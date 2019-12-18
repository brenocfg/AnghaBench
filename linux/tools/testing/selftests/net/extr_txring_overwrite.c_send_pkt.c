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
struct tpacket_hdr {scalar_t__ tp_status; int /*<<< orphan*/  tp_len; } ;

/* Variables and functions */
 scalar_t__ TP_STATUS_AVAILABLE ; 
 scalar_t__ TP_STATUS_SEND_REQUEST ; 
 int /*<<< orphan*/  build_packet (void*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  cfg_frame_size ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int eth_off ; 
 int sendto (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void send_pkt(int fdt, void *slot, char payload_char)
{
	struct tpacket_hdr *header = slot;
	int ret;

	while (header->tp_status != TP_STATUS_AVAILABLE)
		usleep(1000);

	build_packet(slot + eth_off, cfg_frame_size, payload_char);

	header->tp_len = cfg_frame_size;
	header->tp_status = TP_STATUS_SEND_REQUEST;

	ret = sendto(fdt, NULL, 0, 0, NULL, 0);
	if (ret == -1)
		error(1, errno, "kick tx");
}