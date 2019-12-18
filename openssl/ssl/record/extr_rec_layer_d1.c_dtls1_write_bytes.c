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
struct TYPE_5__ {int /*<<< orphan*/  rwstate; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 size_t SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_DTLS1_WRITE_BYTES ; 
 int /*<<< orphan*/  SSL_NOTHING ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_dtls1_write (TYPE_1__*,int,void const*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int dtls1_write_bytes(SSL *s, int type, const void *buf, size_t len,
                      size_t *written)
{
    int i;

    if (!ossl_assert(len <= SSL3_RT_MAX_PLAIN_LENGTH)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DTLS1_WRITE_BYTES,
                 ERR_R_INTERNAL_ERROR);
        return -1;
    }
    s->rwstate = SSL_NOTHING;
    i = do_dtls1_write(s, type, buf, len, 0, written);
    return i;
}