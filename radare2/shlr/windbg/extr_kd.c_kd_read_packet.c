#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {scalar_t__ leader; int length; scalar_t__ checksum; int id; } ;
typedef  TYPE_1__ kd_packet_t ;

/* Variables and functions */
 int KD_E_IOERR ; 
 int KD_E_MALFORMED ; 
 int KD_E_OK ; 
 scalar_t__ KD_PACKET_DATA ; 
 int /*<<< orphan*/  KD_PACKET_TYPE_ACKNOWLEDGE ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ iob_read (void*,int*,int) ; 
 scalar_t__ kd_data_checksum (int*,int) ; 
 int /*<<< orphan*/  kd_packet_is_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  kd_send_ctrl_packet (void*,int /*<<< orphan*/ ,int) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int kd_read_packet(void *fp, kd_packet_t **p) {
	kd_packet_t pkt;
	uint8_t *buf;

	*p = NULL;

	if (iob_read (fp, (uint8_t *) &pkt, sizeof (kd_packet_t)) <= 0) {
		return KD_E_IOERR;
	}

	if (!kd_packet_is_valid (&pkt)) {
		eprintf ("invalid leader %08x\n", pkt.leader);
		return KD_E_MALFORMED;
	}

	buf = malloc (sizeof (kd_packet_t) + pkt.length);
	if (!buf) {
		return KD_E_IOERR;
	}
	memcpy (buf, &pkt, sizeof(kd_packet_t));

	if (pkt.length) {
		iob_read (fp, (uint8_t *) buf + sizeof(kd_packet_t), pkt.length);
	}

	if (pkt.checksum != kd_data_checksum (buf + sizeof(kd_packet_t), pkt.length)) {
		eprintf ("Checksum mismatch!\n");
		free (buf);
		return KD_E_MALFORMED;
	}

	if (pkt.leader == KD_PACKET_DATA) {
		uint8_t trailer;
		iob_read (fp, (uint8_t *) &trailer, 1);

		if (trailer != 0xAA) {
			printf ("Missing trailer 0xAA\n");
			free (buf);
			return KD_E_MALFORMED;
		}

		kd_send_ctrl_packet (fp, KD_PACKET_TYPE_ACKNOWLEDGE, ((kd_packet_t *) buf)->id & ~(0x800));
	}

	*p = (kd_packet_t *) buf;

	return KD_E_OK;
}