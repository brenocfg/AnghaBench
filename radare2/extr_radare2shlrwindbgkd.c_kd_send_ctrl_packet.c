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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  id; scalar_t__ checksum; scalar_t__ length; int /*<<< orphan*/  leader; } ;
typedef  TYPE_1__ kd_packet_t ;

/* Variables and functions */
 int KD_E_IOERR ; 
 int KD_E_OK ; 
 int /*<<< orphan*/  KD_PACKET_CTRL ; 
 scalar_t__ iob_write (void*,int /*<<< orphan*/ *,int) ; 

int kd_send_ctrl_packet(void *fp, const uint32_t type, const uint32_t id) {
	kd_packet_t pkt;

	pkt.leader = KD_PACKET_CTRL;
	pkt.length = 0;
	pkt.checksum = 0;
	pkt.id = id;
	pkt.type = type;

	if (iob_write (fp, (uint8_t *) &pkt, sizeof(kd_packet_t)) < 0) {
		return KD_E_IOERR;
	}

	return KD_E_OK;
}