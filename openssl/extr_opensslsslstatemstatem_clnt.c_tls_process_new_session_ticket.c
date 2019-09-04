#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nonce_label ;
struct TYPE_20__ {TYPE_2__* session; int /*<<< orphan*/  resumption_master_secret; TYPE_15__* session_ctx; } ;
struct TYPE_18__ {unsigned int ticklen; unsigned long tick_lifetime_hint; unsigned long tick_age_add; int /*<<< orphan*/ * tick; } ;
struct TYPE_19__ {unsigned int session_id_length; long time; size_t master_key_length; int /*<<< orphan*/  master_key; scalar_t__ not_resumable; int /*<<< orphan*/  session_id; TYPE_1__ ext; } ;
struct TYPE_17__ {int session_cache_mode; } ;
typedef  TYPE_2__ SSL_SESSION ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  RAW_EXTENSION ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_Digest (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_READING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_FINISHED_READING ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (unsigned int) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_net_4 (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  PACKET_null_init (int /*<<< orphan*/ *) ; 
 unsigned int PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_CTX_remove_session (TYPE_15__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_EXT_TLS1_3_NEW_SESSION_TICKET ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_NEW_SESSION_TICKET ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_2__*) ; 
 int SSL_SESS_CACHE_CLIENT ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/ * ssl_handshake_md (TYPE_3__*) ; 
 TYPE_2__* ssl_session_dup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_update_cache (TYPE_3__*,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls13_hkdf_expand (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char const*,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  tls_collect_extensions (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_parse_all_extensions (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

MSG_PROCESS_RETURN tls_process_new_session_ticket(SSL *s, PACKET *pkt)
{
    unsigned int ticklen;
    unsigned long ticket_lifetime_hint, age_add = 0;
    unsigned int sess_len;
    RAW_EXTENSION *exts = NULL;
    PACKET nonce;

    PACKET_null_init(&nonce);

    if (!PACKET_get_net_4(pkt, &ticket_lifetime_hint)
        || (SSL_IS_TLS13(s)
            && (!PACKET_get_net_4(pkt, &age_add)
                || !PACKET_get_length_prefixed_1(pkt, &nonce)))
        || !PACKET_get_net_2(pkt, &ticklen)
        || (SSL_IS_TLS13(s) ? (ticklen == 0 || PACKET_remaining(pkt) < ticklen)
                            : PACKET_remaining(pkt) != ticklen)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_NEW_SESSION_TICKET,
                 SSL_R_LENGTH_MISMATCH);
        goto err;
    }

    /*
     * Server is allowed to change its mind (in <=TLSv1.2) and send an empty
     * ticket. We already checked this TLSv1.3 case above, so it should never
     * be 0 here in that instance
     */
    if (ticklen == 0)
        return MSG_PROCESS_CONTINUE_READING;

    /*
     * Sessions must be immutable once they go into the session cache. Otherwise
     * we can get multi-thread problems. Therefore we don't "update" sessions,
     * we replace them with a duplicate. In TLSv1.3 we need to do this every
     * time a NewSessionTicket arrives because those messages arrive
     * post-handshake and the session may have already gone into the session
     * cache.
     */
    if (SSL_IS_TLS13(s) || s->session->session_id_length > 0) {
        SSL_SESSION *new_sess;

        /*
         * We reused an existing session, so we need to replace it with a new
         * one
         */
        if ((new_sess = ssl_session_dup(s->session, 0)) == 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_PROCESS_NEW_SESSION_TICKET,
                     ERR_R_MALLOC_FAILURE);
            goto err;
        }

        if ((s->session_ctx->session_cache_mode & SSL_SESS_CACHE_CLIENT) != 0
                && !SSL_IS_TLS13(s)) {
            /*
             * In TLSv1.2 and below the arrival of a new tickets signals that
             * any old ticket we were using is now out of date, so we remove the
             * old session from the cache. We carry on if this fails
             */
            SSL_CTX_remove_session(s->session_ctx, s->session);
        }

        SSL_SESSION_free(s->session);
        s->session = new_sess;
    }

    /*
     * Technically the cast to long here is not guaranteed by the C standard -
     * but we use it elsewhere, so this should be ok.
     */
    s->session->time = (long)time(NULL);

    OPENSSL_free(s->session->ext.tick);
    s->session->ext.tick = NULL;
    s->session->ext.ticklen = 0;

    s->session->ext.tick = OPENSSL_malloc(ticklen);
    if (s->session->ext.tick == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_NEW_SESSION_TICKET,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if (!PACKET_copy_bytes(pkt, s->session->ext.tick, ticklen)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_NEW_SESSION_TICKET,
                 SSL_R_LENGTH_MISMATCH);
        goto err;
    }

    s->session->ext.tick_lifetime_hint = ticket_lifetime_hint;
    s->session->ext.tick_age_add = age_add;
    s->session->ext.ticklen = ticklen;

    if (SSL_IS_TLS13(s)) {
        PACKET extpkt;

        if (!PACKET_as_length_prefixed_2(pkt, &extpkt)
                || PACKET_remaining(pkt) != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PROCESS_NEW_SESSION_TICKET,
                     SSL_R_LENGTH_MISMATCH);
            goto err;
        }

        if (!tls_collect_extensions(s, &extpkt,
                                    SSL_EXT_TLS1_3_NEW_SESSION_TICKET, &exts,
                                    NULL, 1)
                || !tls_parse_all_extensions(s,
                                             SSL_EXT_TLS1_3_NEW_SESSION_TICKET,
                                             exts, NULL, 0, 1)) {
            /* SSLfatal() already called */
            goto err;
        }
    }

    /*
     * There are two ways to detect a resumed ticket session. One is to set
     * an appropriate session ID and then the server must return a match in
     * ServerHello. This allows the normal client session ID matching to work
     * and we know much earlier that the ticket has been accepted. The
     * other way is to set zero length session ID when the ticket is
     * presented and rely on the handshake to determine session resumption.
     * We choose the former approach because this fits in with assumptions
     * elsewhere in OpenSSL. The session ID is set to the SHA256 (or SHA1 is
     * SHA256 is disabled) hash of the ticket.
     */
    /*
     * TODO(size_t): we use sess_len here because EVP_Digest expects an int
     * but s->session->session_id_length is a size_t
     */
    if (!EVP_Digest(s->session->ext.tick, ticklen,
                    s->session->session_id, &sess_len,
                    EVP_sha256(), NULL)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_NEW_SESSION_TICKET,
                 ERR_R_EVP_LIB);
        goto err;
    }
    s->session->session_id_length = sess_len;
    s->session->not_resumable = 0;

    /* This is a standalone message in TLSv1.3, so there is no more to read */
    if (SSL_IS_TLS13(s)) {
        const EVP_MD *md = ssl_handshake_md(s);
        int hashleni = EVP_MD_size(md);
        size_t hashlen;
        static const unsigned char nonce_label[] = "resumption";

        /* Ensure cast to size_t is safe */
        if (!ossl_assert(hashleni >= 0)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_PROCESS_NEW_SESSION_TICKET,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        hashlen = (size_t)hashleni;

        if (!tls13_hkdf_expand(s, md, s->resumption_master_secret,
                               nonce_label,
                               sizeof(nonce_label) - 1,
                               PACKET_data(&nonce),
                               PACKET_remaining(&nonce),
                               s->session->master_key,
                               hashlen, 1)) {
            /* SSLfatal() already called */
            goto err;
        }
        s->session->master_key_length = hashlen;

        OPENSSL_free(exts);
        ssl_update_cache(s, SSL_SESS_CACHE_CLIENT);
        return MSG_PROCESS_FINISHED_READING;
    }

    return MSG_PROCESS_CONTINUE_READING;
 err:
    OPENSSL_free(exts);
    return MSG_PROCESS_ERROR;
}