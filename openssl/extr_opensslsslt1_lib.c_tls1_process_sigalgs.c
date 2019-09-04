#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {size_t shared_sigalgslen; TYPE_4__** shared_sigalgs; } ;
struct TYPE_12__ {int sig_idx; scalar_t__ sig; } ;
struct TYPE_9__ {int* valid_flags; } ;
struct TYPE_10__ {TYPE_1__ tmp; } ;
struct TYPE_11__ {TYPE_5__* cert; TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ SIGALG_LOOKUP ;
typedef  TYPE_5__ CERT ;

/* Variables and functions */
 int CERT_PKEY_EXPLICIT_SIGN ; 
 int CERT_PKEY_SIGN ; 
 scalar_t__ EVP_PKEY_RSA ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 size_t SSL_PKEY_NUM ; 
 int /*<<< orphan*/  ssl_cert_is_disabled (int) ; 
 int /*<<< orphan*/  tls1_set_shared_sigalgs (TYPE_3__*) ; 

int tls1_process_sigalgs(SSL *s)
{
    size_t i;
    uint32_t *pvalid = s->s3.tmp.valid_flags;
    CERT *c = s->cert;

    if (!tls1_set_shared_sigalgs(s))
        return 0;

    for (i = 0; i < SSL_PKEY_NUM; i++)
        pvalid[i] = 0;

    for (i = 0; i < c->shared_sigalgslen; i++) {
        const SIGALG_LOOKUP *sigptr = c->shared_sigalgs[i];
        int idx = sigptr->sig_idx;

        /* Ignore PKCS1 based sig algs in TLSv1.3 */
        if (SSL_IS_TLS13(s) && sigptr->sig == EVP_PKEY_RSA)
            continue;
        /* If not disabled indicate we can explicitly sign */
        if (pvalid[idx] == 0 && !ssl_cert_is_disabled(idx))
            pvalid[idx] = CERT_PKEY_EXPLICIT_SIGN | CERT_PKEY_SIGN;
    }
    return 1;
}