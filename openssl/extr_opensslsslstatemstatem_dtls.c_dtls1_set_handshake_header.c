#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_7__ {TYPE_1__* d1; } ;
struct TYPE_6__ {int /*<<< orphan*/  handshake_write_seq; int /*<<< orphan*/  next_handshake_write_seq; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  DTLS1_HM_HEADER_LENGTH ; 
 int /*<<< orphan*/  SSL3_MT_CCS ; 
 int SSL3_MT_CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  WPACKET_allocate_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtls1_set_message_header (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtls1_set_message_header_int (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dtls1_set_handshake_header(SSL *s, WPACKET *pkt, int htype)
{
    unsigned char *header;

    if (htype == SSL3_MT_CHANGE_CIPHER_SPEC) {
        s->d1->handshake_write_seq = s->d1->next_handshake_write_seq;
        dtls1_set_message_header_int(s, SSL3_MT_CCS, 0,
                                     s->d1->handshake_write_seq, 0, 0);
        if (!WPACKET_put_bytes_u8(pkt, SSL3_MT_CCS))
            return 0;
    } else {
        dtls1_set_message_header(s, htype, 0, 0, 0);
        /*
         * We allocate space at the start for the message header. This gets
         * filled in later
         */
        if (!WPACKET_allocate_bytes(pkt, DTLS1_HM_HEADER_LENGTH, &header)
                || !WPACKET_start_sub_packet(pkt))
            return 0;
    }

    return 1;
}