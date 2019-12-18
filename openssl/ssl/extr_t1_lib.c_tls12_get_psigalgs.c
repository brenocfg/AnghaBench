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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int server; TYPE_1__* cert; } ;
struct TYPE_5__ {size_t client_sigalgslen; size_t conf_sigalgslen; int /*<<< orphan*/ * conf_sigalgs; int /*<<< orphan*/ * client_sigalgs; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 size_t OSSL_NELEM (int /*<<< orphan*/ *) ; 
#define  SSL_CERT_FLAG_SUITEB_128_LOS 130 
#define  SSL_CERT_FLAG_SUITEB_128_LOS_ONLY 129 
#define  SSL_CERT_FLAG_SUITEB_192_LOS 128 
 int /*<<< orphan*/ * suiteb_sigalgs ; 
 int /*<<< orphan*/ * tls12_sigalgs ; 
 int tls1_suiteb (TYPE_2__*) ; 

size_t tls12_get_psigalgs(SSL *s, int sent, const uint16_t **psigs)
{
    /*
     * If Suite B mode use Suite B sigalgs only, ignore any other
     * preferences.
     */
#ifndef OPENSSL_NO_EC
    switch (tls1_suiteb(s)) {
    case SSL_CERT_FLAG_SUITEB_128_LOS:
        *psigs = suiteb_sigalgs;
        return OSSL_NELEM(suiteb_sigalgs);

    case SSL_CERT_FLAG_SUITEB_128_LOS_ONLY:
        *psigs = suiteb_sigalgs;
        return 1;

    case SSL_CERT_FLAG_SUITEB_192_LOS:
        *psigs = suiteb_sigalgs + 1;
        return 1;
    }
#endif
    /*
     *  We use client_sigalgs (if not NULL) if we're a server
     *  and sending a certificate request or if we're a client and
     *  determining which shared algorithm to use.
     */
    if ((s->server == sent) && s->cert->client_sigalgs != NULL) {
        *psigs = s->cert->client_sigalgs;
        return s->cert->client_sigalgslen;
    } else if (s->cert->conf_sigalgs) {
        *psigs = s->cert->conf_sigalgs;
        return s->cert->conf_sigalgslen;
    } else {
        *psigs = tls12_sigalgs;
        return OSSL_NELEM(tls12_sigalgs);
    }
}