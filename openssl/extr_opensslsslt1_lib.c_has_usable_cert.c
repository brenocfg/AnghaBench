#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int sig_idx; int hash; int sig; } ;
struct TYPE_11__ {size_t peer_cert_sigalgslen; int /*<<< orphan*/ * peer_cert_sigalgs; } ;
struct TYPE_12__ {TYPE_1__ tmp; } ;
struct TYPE_15__ {TYPE_4__* cert; TYPE_2__ s3; } ;
struct TYPE_14__ {TYPE_3__* pkeys; } ;
struct TYPE_13__ {int /*<<< orphan*/  privatekey; int /*<<< orphan*/  x509; } ;
typedef  TYPE_5__ SSL ;
typedef  TYPE_6__ SIGALG_LOOKUP ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_pop_to_mark () ; 
 int /*<<< orphan*/  ERR_set_mark () ; 
 int EVP_PKEY_supports_digest_nid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  X509_get_signature_info (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_has_cert (TYPE_5__*,int) ; 
 TYPE_6__* tls1_lookup_sigalg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int has_usable_cert(SSL *s, const SIGALG_LOOKUP *sig, int idx)
{
    const SIGALG_LOOKUP *lu;
    int mdnid, pknid, supported;
    size_t i;

    /* TLS 1.2 callers can override lu->sig_idx, but not TLS 1.3 callers. */
    if (idx == -1)
        idx = sig->sig_idx;
    if (!ssl_has_cert(s, idx))
        return 0;
    if (s->s3.tmp.peer_cert_sigalgs != NULL) {
        for (i = 0; i < s->s3.tmp.peer_cert_sigalgslen; i++) {
            lu = tls1_lookup_sigalg(s->s3.tmp.peer_cert_sigalgs[i]);
            if (lu == NULL
                || !X509_get_signature_info(s->cert->pkeys[idx].x509, &mdnid,
                                            &pknid, NULL, NULL)
                /*
                 * TODO this does not differentiate between the
                 * rsa_pss_pss_* and rsa_pss_rsae_* schemes since we do not
                 * have a chain here that lets us look at the key OID in the
                 * signing certificate.
                 */
                || mdnid != lu->hash
                || pknid != lu->sig)
                continue;

            ERR_set_mark();
            supported = EVP_PKEY_supports_digest_nid(s->cert->pkeys[idx].privatekey,
                                                     mdnid);
            if (supported == 0)
                continue;
            else if (supported < 0)
            {
                /* If it didn't report a mandatory NID, for whatever reasons,
                 * just clear the error and allow all hashes to be used. */
                ERR_pop_to_mark();
            }
            return 1;
        }
        return 0;
    }
    supported = EVP_PKEY_supports_digest_nid(s->cert->pkeys[idx].privatekey,
                                             sig->hash);
    if (supported == 0)
        return 0;
    else if (supported < 0)
        ERR_clear_error();

    return 1;
}