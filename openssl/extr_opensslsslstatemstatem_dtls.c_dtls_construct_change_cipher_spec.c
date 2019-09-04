#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_6__ {scalar_t__ version; TYPE_1__* d1; } ;
struct TYPE_5__ {int /*<<< orphan*/  handshake_write_seq; int /*<<< orphan*/  next_handshake_write_seq; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 scalar_t__ DTLS1_BAD_VER ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_DTLS_CONSTRUCT_CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dtls_construct_change_cipher_spec(SSL *s, WPACKET *pkt)
{
    if (s->version == DTLS1_BAD_VER) {
        s->d1->next_handshake_write_seq++;

        if (!WPACKET_put_bytes_u16(pkt, s->d1->handshake_write_seq)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_DTLS_CONSTRUCT_CHANGE_CIPHER_SPEC,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }

    return 1;
}