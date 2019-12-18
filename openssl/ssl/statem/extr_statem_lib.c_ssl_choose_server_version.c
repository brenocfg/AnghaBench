#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {unsigned int version; TYPE_2__* (* smeth ) () ;} ;
typedef  TYPE_1__ version_info ;
struct TYPE_23__ {int legacy_version; TYPE_4__* pre_proc_exts; } ;
struct TYPE_22__ {int parsed; int /*<<< orphan*/  data; scalar_t__ present; } ;
struct TYPE_21__ {int client_version; unsigned int version; scalar_t__ hello_retry_request; TYPE_2__ const* method; } ;
struct TYPE_20__ {int version; } ;
typedef  TYPE_2__ SSL_METHOD ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ RAW_EXTENSION ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  DOWNGRADE ;
typedef  TYPE_5__ CLIENTHELLO_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  DOWNGRADE_NONE ; 
#define  DTLS_ANY_VERSION 129 
 int /*<<< orphan*/  PACKET_as_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int SSL3_VERSION ; 
 scalar_t__ SSL_HRR_NONE ; 
 int /*<<< orphan*/  SSL_IS_DTLS (TYPE_3__*) ; 
 int /*<<< orphan*/  SSL_IS_TLS13 (TYPE_3__*) ; 
 int SSL_R_BAD_LEGACY_VERSION ; 
 int SSL_R_LENGTH_MISMATCH ; 
 int SSL_R_UNSUPPORTED_PROTOCOL ; 
 int SSL_R_VERSION_TOO_LOW ; 
 int SSL_R_WRONG_SSL_VERSION ; 
 int TLS1_2_VERSION ; 
 unsigned int TLS1_3_VERSION ; 
 size_t TLSEXT_IDX_supported_versions ; 
#define  TLS_ANY_VERSION 128 
 int /*<<< orphan*/  check_for_downgrade (TYPE_3__*,unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_1__* dtls_version_table ; 
 scalar_t__ ssl_method_error (TYPE_3__*,TYPE_2__ const*) ; 
 scalar_t__ ssl_version_supported (TYPE_3__*,unsigned int,TYPE_2__ const**) ; 
 TYPE_2__* stub1 () ; 
 TYPE_1__* tls_version_table ; 
 scalar_t__ version_cmp (TYPE_3__*,int,unsigned int) ; 

int ssl_choose_server_version(SSL *s, CLIENTHELLO_MSG *hello, DOWNGRADE *dgrd)
{
    /*-
     * With version-flexible methods we have an initial state with:
     *
     *   s->method->version == (D)TLS_ANY_VERSION,
     *   s->version == (D)TLS_MAX_VERSION_INTERNAL.
     *
     * So we detect version-flexible methods via the method version, not the
     * handle version.
     */
    int server_version = s->method->version;
    int client_version = hello->legacy_version;
    const version_info *vent;
    const version_info *table;
    int disabled = 0;
    RAW_EXTENSION *suppversions;

    s->client_version = client_version;

    switch (server_version) {
    default:
        if (!SSL_IS_TLS13(s)) {
            if (version_cmp(s, client_version, s->version) < 0)
                return SSL_R_WRONG_SSL_VERSION;
            *dgrd = DOWNGRADE_NONE;
            /*
             * If this SSL handle is not from a version flexible method we don't
             * (and never did) check min/max FIPS or Suite B constraints.  Hope
             * that's OK.  It is up to the caller to not choose fixed protocol
             * versions they don't want.  If not, then easy to fix, just return
             * ssl_method_error(s, s->method)
             */
            return 0;
        }
        /*
         * Fall through if we are TLSv1.3 already (this means we must be after
         * a HelloRetryRequest
         */
        /* fall thru */
    case TLS_ANY_VERSION:
        table = tls_version_table;
        break;
    case DTLS_ANY_VERSION:
        table = dtls_version_table;
        break;
    }

    suppversions = &hello->pre_proc_exts[TLSEXT_IDX_supported_versions];

    /* If we did an HRR then supported versions is mandatory */
    if (!suppversions->present && s->hello_retry_request != SSL_HRR_NONE)
        return SSL_R_UNSUPPORTED_PROTOCOL;

    if (suppversions->present && !SSL_IS_DTLS(s)) {
        unsigned int candidate_vers = 0;
        unsigned int best_vers = 0;
        const SSL_METHOD *best_method = NULL;
        PACKET versionslist;

        suppversions->parsed = 1;

        if (!PACKET_as_length_prefixed_1(&suppversions->data, &versionslist)) {
            /* Trailing or invalid data? */
            return SSL_R_LENGTH_MISMATCH;
        }

        /*
         * The TLSv1.3 spec says the client MUST set this to TLS1_2_VERSION.
         * The spec only requires servers to check that it isn't SSLv3:
         * "Any endpoint receiving a Hello message with
         * ClientHello.legacy_version or ServerHello.legacy_version set to
         * 0x0300 MUST abort the handshake with a "protocol_version" alert."
         * We are slightly stricter and require that it isn't SSLv3 or lower.
         * We tolerate TLSv1 and TLSv1.1.
         */
        if (client_version <= SSL3_VERSION)
            return SSL_R_BAD_LEGACY_VERSION;

        while (PACKET_get_net_2(&versionslist, &candidate_vers)) {
            if (version_cmp(s, candidate_vers, best_vers) <= 0)
                continue;
            if (ssl_version_supported(s, candidate_vers, &best_method))
                best_vers = candidate_vers;
        }
        if (PACKET_remaining(&versionslist) != 0) {
            /* Trailing data? */
            return SSL_R_LENGTH_MISMATCH;
        }

        if (best_vers > 0) {
            if (s->hello_retry_request != SSL_HRR_NONE) {
                /*
                 * This is after a HelloRetryRequest so we better check that we
                 * negotiated TLSv1.3
                 */
                if (best_vers != TLS1_3_VERSION)
                    return SSL_R_UNSUPPORTED_PROTOCOL;
                return 0;
            }
            check_for_downgrade(s, best_vers, dgrd);
            s->version = best_vers;
            s->method = best_method;
            return 0;
        }
        return SSL_R_UNSUPPORTED_PROTOCOL;
    }

    /*
     * If the supported versions extension isn't present, then the highest
     * version we can negotiate is TLSv1.2
     */
    if (version_cmp(s, client_version, TLS1_3_VERSION) >= 0)
        client_version = TLS1_2_VERSION;

    /*
     * No supported versions extension, so we just use the version supplied in
     * the ClientHello.
     */
    for (vent = table; vent->version != 0; ++vent) {
        const SSL_METHOD *method;

        if (vent->smeth == NULL ||
            version_cmp(s, client_version, vent->version) < 0)
            continue;
        method = vent->smeth();
        if (ssl_method_error(s, method) == 0) {
            check_for_downgrade(s, vent->version, dgrd);
            s->version = vent->version;
            s->method = method;
            return 0;
        }
        disabled = 1;
    }
    return disabled ? SSL_R_UNSUPPORTED_PROTOCOL : SSL_R_VERSION_TOO_LOW;
}