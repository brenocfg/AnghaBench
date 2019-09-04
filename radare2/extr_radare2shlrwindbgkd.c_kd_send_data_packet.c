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
typedef  int uint32_t ;
struct TYPE_2__ {int length; int id; int type; scalar_t__ checksum; int /*<<< orphan*/  leader; } ;
typedef  TYPE_1__ kd_packet_t ;

/* Variables and functions */
 int KD_E_IOERR ; 
 int KD_E_MALFORMED ; 
 int KD_E_OK ; 
 int const KD_MAX_PAYLOAD ; 
 int /*<<< orphan*/  KD_PACKET_DATA ; 
 scalar_t__ iob_write (void*,int /*<<< orphan*/ *,int const) ; 
 scalar_t__ kd_data_checksum (int /*<<< orphan*/  const*,int const) ; 

int kd_send_data_packet(void *fp, const uint32_t type, const uint32_t id, const uint8_t *req,
			const int req_len, const uint8_t *buf, const uint32_t buf_len) {
	kd_packet_t pkt;

	if (req_len + buf_len > KD_MAX_PAYLOAD) {
		return KD_E_MALFORMED;
	}

	//kd_req_t *r = (kd_req_t*) req;
	//eprintf ("==== Send ====\n%08x\n", r->req);

	pkt.leader = KD_PACKET_DATA;
	pkt.length = req_len + buf_len;
	pkt.checksum = kd_data_checksum (req, req_len) +
		       kd_data_checksum (buf, buf_len);
	pkt.id = id;
	pkt.type = type;

	if (iob_write (fp, (uint8_t *) &pkt, sizeof(kd_packet_t)) < 0) {
		return KD_E_IOERR;
	}

	if (iob_write (fp, (uint8_t *) req, req_len) < 0) {
		return KD_E_IOERR;
	}

	if (buf && iob_write (fp, (uint8_t *) buf, buf_len) < 0) {
		return KD_E_IOERR;
	}

	if (iob_write (fp, (uint8_t *) "\xAA", 1) < 0) {
		return KD_E_IOERR;
	}

	return KD_E_OK;
}