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
struct TYPE_7__ {TYPE_1__* session; } ;
struct TYPE_6__ {int /*<<< orphan*/  session_id_length; int /*<<< orphan*/  session_id; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_CONSTRUCT_STATEFUL_TICKET ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ticket_prequel (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int construct_stateful_ticket(SSL *s, WPACKET *pkt, uint32_t age_add,
                                     unsigned char *tick_nonce)
{
    if (!create_ticket_prequel(s, pkt, age_add, tick_nonce)) {
        /* SSLfatal() already called */
        return 0;
    }

    if (!WPACKET_memcpy(pkt, s->session->session_id,
                        s->session->session_id_length)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_CONSTRUCT_STATEFUL_TICKET,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    return 1;
}