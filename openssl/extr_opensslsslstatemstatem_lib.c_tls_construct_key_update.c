#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_4__ {int /*<<< orphan*/  key_update; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_KEY_UPDATE ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_NONE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int tls_construct_key_update(SSL *s, WPACKET *pkt)
{
    if (!WPACKET_put_bytes_u8(pkt, s->key_update)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_KEY_UPDATE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    s->key_update = SSL_KEY_UPDATE_NONE;
    return 1;
}