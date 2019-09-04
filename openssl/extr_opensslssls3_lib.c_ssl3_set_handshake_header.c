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
typedef  int /*<<< orphan*/  WPACKET ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int SSL3_MT_CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u24 (int /*<<< orphan*/ *) ; 

int ssl3_set_handshake_header(SSL *s, WPACKET *pkt, int htype)
{
    /* No header in the event of a CCS */
    if (htype == SSL3_MT_CHANGE_CIPHER_SPEC)
        return 1;

    /* Set the content type and 3 bytes for the message len */
    if (!WPACKET_put_bytes_u8(pkt, htype)
            || !WPACKET_start_sub_packet_u24(pkt))
        return 0;

    return 1;
}