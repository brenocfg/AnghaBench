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
struct TYPE_5__ {int /*<<< orphan*/ * handshake_dgst; int /*<<< orphan*/  handshake_buffer; } ;
struct TYPE_6__ {TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int BIO_write (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_FINISH_MAC ; 
 int /*<<< orphan*/  SSL_R_OVERFLOW_ERROR ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ssl3_finish_mac(SSL *s, const unsigned char *buf, size_t len)
{
    int ret;

    if (s->s3.handshake_dgst == NULL) {
        /* Note: this writes to a memory BIO so a failure is a fatal error */
        if (len > INT_MAX) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_FINISH_MAC,
                     SSL_R_OVERFLOW_ERROR);
            return 0;
        }
        ret = BIO_write(s->s3.handshake_buffer, (void *)buf, (int)len);
        if (ret <= 0 || ret != (int)len) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_FINISH_MAC,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    } else {
        ret = EVP_DigestUpdate(s->s3.handshake_dgst, buf, len);
        if (!ret) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_FINISH_MAC,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }
    return 1;
}