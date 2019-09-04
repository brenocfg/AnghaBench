#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_8__ {int /*<<< orphan*/ * cert; } ;
struct TYPE_9__ {TYPE_1__ tmp; } ;
struct TYPE_10__ {TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  CERT_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_SERVER_CERTIFICATE ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_output_cert_chain (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int tls_construct_server_certificate(SSL *s, WPACKET *pkt)
{
    CERT_PKEY *cpk = s->s3.tmp.cert;

    if (cpk == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_SERVER_CERTIFICATE, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /*
     * In TLSv1.3 the certificate chain is always preceded by a 0 length context
     * for the server Certificate message
     */
    if (SSL_IS_TLS13(s) && !WPACKET_put_bytes_u8(pkt, 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_SERVER_CERTIFICATE, ERR_R_INTERNAL_ERROR);
        return 0;
    }
    if (!ssl3_output_cert_chain(s, pkt, cpk)) {
        /* SSLfatal() already called */
        return 0;
    }

    return 1;
}