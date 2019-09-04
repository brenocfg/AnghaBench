#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_16__ {scalar_t__ const sigalg; } ;
struct TYPE_12__ {scalar_t__* valid_flags; int /*<<< orphan*/ * peer_sigalgs; int /*<<< orphan*/ * peer_cert_sigalgs; } ;
struct TYPE_13__ {TYPE_1__ tmp; } ;
struct TYPE_15__ {TYPE_3__* cert; TYPE_2__ s3; } ;
struct TYPE_14__ {int /*<<< orphan*/ * shared_sigalgs; scalar_t__ shared_sigalgslen; } ;
typedef  TYPE_4__ SSL ;
typedef  TYPE_5__ SIGALG_LOOKUP ;

/* Variables and functions */
 scalar_t__ CERT_PKEY_SIGN ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS1_SET_SERVER_SIGALGS ; 
 size_t SSL_PKEY_NUM ; 
 int /*<<< orphan*/  SSL_R_NO_SHARED_SIGNATURE_ALGORITHMS ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t tls12_get_psigalgs (TYPE_4__*,int,scalar_t__ const**) ; 
 TYPE_5__* tls1_get_legacy_sigalg (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  tls1_process_sigalgs (TYPE_4__*) ; 

int tls1_set_server_sigalgs(SSL *s)
{
    size_t i;

    /* Clear any shared signature algorithms */
    OPENSSL_free(s->cert->shared_sigalgs);
    s->cert->shared_sigalgs = NULL;
    s->cert->shared_sigalgslen = 0;
    /* Clear certificate validity flags */
    for (i = 0; i < SSL_PKEY_NUM; i++)
        s->s3.tmp.valid_flags[i] = 0;
    /*
     * If peer sent no signature algorithms check to see if we support
     * the default algorithm for each certificate type
     */
    if (s->s3.tmp.peer_cert_sigalgs == NULL
            && s->s3.tmp.peer_sigalgs == NULL) {
        const uint16_t *sent_sigs;
        size_t sent_sigslen = tls12_get_psigalgs(s, 1, &sent_sigs);

        for (i = 0; i < SSL_PKEY_NUM; i++) {
            const SIGALG_LOOKUP *lu = tls1_get_legacy_sigalg(s, i);
            size_t j;

            if (lu == NULL)
                continue;
            /* Check default matches a type we sent */
            for (j = 0; j < sent_sigslen; j++) {
                if (lu->sigalg == sent_sigs[j]) {
                        s->s3.tmp.valid_flags[i] = CERT_PKEY_SIGN;
                        break;
                }
            }
        }
        return 1;
    }

    if (!tls1_process_sigalgs(s)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS1_SET_SERVER_SIGALGS, ERR_R_INTERNAL_ERROR);
        return 0;
    }
    if (s->cert->shared_sigalgs != NULL)
        return 1;

    /* Fatal error if no shared signature algorithms */
    SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS1_SET_SERVER_SIGALGS,
             SSL_R_NO_SHARED_SIGNATURE_ALGORITHMS);
    return 0;
}