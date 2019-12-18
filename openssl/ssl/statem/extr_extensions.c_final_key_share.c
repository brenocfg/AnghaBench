#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
struct TYPE_12__ {int psk_kex_mode; int /*<<< orphan*/  cookieok; } ;
struct TYPE_11__ {int flags; unsigned int group_id; int /*<<< orphan*/ * peer_tmp; } ;
struct TYPE_13__ {scalar_t__ hello_retry_request; TYPE_2__ ext; TYPE_1__ s3; int /*<<< orphan*/  hit; scalar_t__ server; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_MISSING_EXTENSION ; 
 unsigned int SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST ; 
 int /*<<< orphan*/  SSL_F_FINAL_KEY_SHARE ; 
 scalar_t__ SSL_HRR_COMPLETE ; 
 scalar_t__ SSL_HRR_NONE ; 
 scalar_t__ SSL_HRR_PENDING ; 
 int /*<<< orphan*/  SSL_IS_TLS13 (TYPE_3__*) ; 
 int /*<<< orphan*/  SSL_R_NO_SUITABLE_KEY_SHARE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS1_FLAGS_STATELESS ; 
 int TLSEXT_KEX_MODE_FLAG_KE ; 
 int TLSEXT_KEX_MODE_FLAG_KE_DHE ; 
 scalar_t__ check_in_list (TYPE_3__*,unsigned int,unsigned int const*,size_t,int) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  tls13_generate_handshake_secret (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls1_get_peer_groups (TYPE_3__*,unsigned int const**,size_t*) ; 
 int /*<<< orphan*/  tls1_get_supported_groups (TYPE_3__*,unsigned int const**,size_t*) ; 

__attribute__((used)) static int final_key_share(SSL *s, unsigned int context, int sent)
{
#if !defined(OPENSSL_NO_TLS1_3)
    if (!SSL_IS_TLS13(s))
        return 1;

    /* Nothing to do for key_share in an HRR */
    if ((context & SSL_EXT_TLS1_3_HELLO_RETRY_REQUEST) != 0)
        return 1;

    /*
     * If
     *     we are a client
     *     AND
     *     we have no key_share
     *     AND
     *     (we are not resuming
     *      OR the kex_mode doesn't allow non key_share resumes)
     * THEN
     *     fail;
     */
    if (!s->server
            && !sent
            && (!s->hit
                || (s->ext.psk_kex_mode & TLSEXT_KEX_MODE_FLAG_KE) == 0)) {
        /* Nothing left we can do - just fail */
        SSLfatal(s, SSL_AD_MISSING_EXTENSION, SSL_F_FINAL_KEY_SHARE,
                 SSL_R_NO_SUITABLE_KEY_SHARE);
        return 0;
    }
    /*
     * IF
     *     we are a server
     * THEN
     *     IF
     *         we have a suitable key_share
     *     THEN
     *         IF
     *             we are stateless AND we have no cookie
     *         THEN
     *             send a HelloRetryRequest
     *     ELSE
     *         IF
     *             we didn't already send a HelloRetryRequest
     *             AND
     *             the client sent a key_share extension
     *             AND
     *             (we are not resuming
     *              OR the kex_mode allows key_share resumes)
     *             AND
     *             a shared group exists
     *         THEN
     *             send a HelloRetryRequest
     *         ELSE IF
     *             we are not resuming
     *             OR
     *             the kex_mode doesn't allow non key_share resumes
     *         THEN
     *             fail
     *         ELSE IF
     *             we are stateless AND we have no cookie
     *         THEN
     *             send a HelloRetryRequest
     */
    if (s->server) {
        if (s->s3.peer_tmp != NULL) {
            /* We have a suitable key_share */
            if ((s->s3.flags & TLS1_FLAGS_STATELESS) != 0
                    && !s->ext.cookieok) {
                if (!ossl_assert(s->hello_retry_request == SSL_HRR_NONE)) {
                    /*
                     * If we are stateless then we wouldn't know about any
                     * previously sent HRR - so how can this be anything other
                     * than 0?
                     */
                    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_FINAL_KEY_SHARE,
                             ERR_R_INTERNAL_ERROR);
                    return 0;
                }
                s->hello_retry_request = SSL_HRR_PENDING;
                return 1;
            }
        } else {
            /* No suitable key_share */
            if (s->hello_retry_request == SSL_HRR_NONE && sent
                    && (!s->hit
                        || (s->ext.psk_kex_mode & TLSEXT_KEX_MODE_FLAG_KE_DHE)
                           != 0)) {
                const uint16_t *pgroups, *clntgroups;
                size_t num_groups, clnt_num_groups, i;
                unsigned int group_id = 0;

                /* Check if a shared group exists */

                /* Get the clients list of supported groups. */
                tls1_get_peer_groups(s, &clntgroups, &clnt_num_groups);
                tls1_get_supported_groups(s, &pgroups, &num_groups);

                /*
                 * Find the first group we allow that is also in client's list
                 */
                for (i = 0; i < num_groups; i++) {
                    group_id = pgroups[i];

                    if (check_in_list(s, group_id, clntgroups, clnt_num_groups,
                                      1))
                        break;
                }

                if (i < num_groups) {
                    /* A shared group exists so send a HelloRetryRequest */
                    s->s3.group_id = group_id;
                    s->hello_retry_request = SSL_HRR_PENDING;
                    return 1;
                }
            }
            if (!s->hit
                    || (s->ext.psk_kex_mode & TLSEXT_KEX_MODE_FLAG_KE) == 0) {
                /* Nothing left we can do - just fail */
                SSLfatal(s, sent ? SSL_AD_HANDSHAKE_FAILURE
                                 : SSL_AD_MISSING_EXTENSION,
                         SSL_F_FINAL_KEY_SHARE, SSL_R_NO_SUITABLE_KEY_SHARE);
                return 0;
            }

            if ((s->s3.flags & TLS1_FLAGS_STATELESS) != 0
                    && !s->ext.cookieok) {
                if (!ossl_assert(s->hello_retry_request == SSL_HRR_NONE)) {
                    /*
                     * If we are stateless then we wouldn't know about any
                     * previously sent HRR - so how can this be anything other
                     * than 0?
                     */
                    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_FINAL_KEY_SHARE,
                             ERR_R_INTERNAL_ERROR);
                    return 0;
                }
                s->hello_retry_request = SSL_HRR_PENDING;
                return 1;
            }
        }

        /*
         * We have a key_share so don't send any more HelloRetryRequest
         * messages
         */
        if (s->hello_retry_request == SSL_HRR_PENDING)
            s->hello_retry_request = SSL_HRR_COMPLETE;
    } else {
        /*
         * For a client side resumption with no key_share we need to generate
         * the handshake secret (otherwise this is done during key_share
         * processing).
         */
        if (!sent && !tls13_generate_handshake_secret(s, NULL, 0)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_FINAL_KEY_SHARE,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }
#endif /* !defined(OPENSSL_NO_TLS1_3) */
    return 1;
}