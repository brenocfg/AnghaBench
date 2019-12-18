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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_7__ {TYPE_1__* session; scalar_t__ hit; } ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_CREATE_TICKET_PREQUEL ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_2__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TICKET_NONCE_SIZE ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_ticket_prequel(SSL *s, WPACKET *pkt, uint32_t age_add,
                                 unsigned char *tick_nonce)
{
    /*
     * Ticket lifetime hint: For TLSv1.2 this is advisory only and we leave this
     * unspecified for resumed session (for simplicity).
     * In TLSv1.3 we reset the "time" field above, and always specify the
     * timeout.
     */
    if (!WPACKET_put_bytes_u32(pkt,
                               (s->hit && !SSL_IS_TLS13(s))
                               ? 0 : s->session->timeout)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_CREATE_TICKET_PREQUEL,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (SSL_IS_TLS13(s)) {
        if (!WPACKET_put_bytes_u32(pkt, age_add)
                || !WPACKET_sub_memcpy_u8(pkt, tick_nonce, TICKET_NONCE_SIZE)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_CREATE_TICKET_PREQUEL,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }

    /* Start the sub-packet for the actual ticket data */
    if (!WPACKET_start_sub_packet_u16(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_CREATE_TICKET_PREQUEL,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    return 1;
}