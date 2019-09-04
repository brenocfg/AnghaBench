#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  psk ;
typedef  int /*<<< orphan*/  identity ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_18__ {int early_data_ok; int /*<<< orphan*/  early_data; int /*<<< orphan*/  alpn_len; int /*<<< orphan*/ * alpn; int /*<<< orphan*/ * hostname; } ;
struct TYPE_20__ {scalar_t__ hello_retry_request; size_t (* psk_client_callback ) (TYPE_4__*,int /*<<< orphan*/ *,char*,int,unsigned char*,int) ;size_t psksession_id_len; scalar_t__ early_data_state; scalar_t__ max_early_data; TYPE_2__ ext; TYPE_3__* session; int /*<<< orphan*/ * psksession_id; TYPE_3__* psksession; int /*<<< orphan*/  (* psk_use_session_cb ) (TYPE_4__*,int /*<<< orphan*/  const*,unsigned char const**,size_t*,TYPE_3__**) ;} ;
struct TYPE_17__ {scalar_t__ max_early_data; int /*<<< orphan*/  alpn_selected_len; int /*<<< orphan*/ * alpn_selected; int /*<<< orphan*/ * hostname; } ;
struct TYPE_19__ {scalar_t__ ssl_version; TYPE_1__ ext; } ;
typedef  TYPE_3__ SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  EXT_RETURN ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_memdup (unsigned char const*,size_t) ; 
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PACKET_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PSK_MAX_IDENTITY_LEN ; 
 int PSK_MAX_PSK_LEN ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/ * SSL_CIPHER_find (TYPE_4__*,unsigned char const*) ; 
 scalar_t__ SSL_EARLY_DATA_CONNECTING ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_REJECTED ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA ; 
 scalar_t__ SSL_HRR_PENDING ; 
 int /*<<< orphan*/  SSL_R_BAD_PSK ; 
 int /*<<< orphan*/  SSL_R_INCONSISTENT_EARLY_DATA_ALPN ; 
 int /*<<< orphan*/  SSL_R_INCONSISTENT_EARLY_DATA_SNI ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_3__*) ; 
 TYPE_3__* SSL_SESSION_new () ; 
 int /*<<< orphan*/  SSL_SESSION_set1_master_key (TYPE_3__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  SSL_SESSION_set_cipher (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_SESSION_set_protocol_version (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLSEXT_TYPE_early_data ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ssl_handshake_md (TYPE_4__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/  const*,unsigned char const**,size_t*,TYPE_3__**) ; 
 size_t stub2 (TYPE_4__*,int /*<<< orphan*/ *,char*,int,unsigned char*,int) ; 

EXT_RETURN tls_construct_ctos_early_data(SSL *s, WPACKET *pkt,
                                         unsigned int context, X509 *x,
                                         size_t chainidx)
{
#ifndef OPENSSL_NO_PSK
    char identity[PSK_MAX_IDENTITY_LEN + 1];
#endif  /* OPENSSL_NO_PSK */
    const unsigned char *id = NULL;
    size_t idlen = 0;
    SSL_SESSION *psksess = NULL;
    SSL_SESSION *edsess = NULL;
    const EVP_MD *handmd = NULL;

    if (s->hello_retry_request == SSL_HRR_PENDING)
        handmd = ssl_handshake_md(s);

    if (s->psk_use_session_cb != NULL
            && (!s->psk_use_session_cb(s, handmd, &id, &idlen, &psksess)
                || (psksess != NULL
                    && psksess->ssl_version != TLS1_3_VERSION))) {
        SSL_SESSION_free(psksess);
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA,
                 SSL_R_BAD_PSK);
        return EXT_RETURN_FAIL;
    }

#ifndef OPENSSL_NO_PSK
    if (psksess == NULL && s->psk_client_callback != NULL) {
        unsigned char psk[PSK_MAX_PSK_LEN];
        size_t psklen = 0;

        memset(identity, 0, sizeof(identity));
        psklen = s->psk_client_callback(s, NULL, identity, sizeof(identity) - 1,
                                        psk, sizeof(psk));

        if (psklen > PSK_MAX_PSK_LEN) {
            SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                     SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA, ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        } else if (psklen > 0) {
            const unsigned char tls13_aes128gcmsha256_id[] = { 0x13, 0x01 };
            const SSL_CIPHER *cipher;

            idlen = strlen(identity);
            if (idlen > PSK_MAX_IDENTITY_LEN) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA,
                         ERR_R_INTERNAL_ERROR);
                return EXT_RETURN_FAIL;
            }
            id = (unsigned char *)identity;

            /*
             * We found a PSK using an old style callback. We don't know
             * the digest so we default to SHA256 as per the TLSv1.3 spec
             */
            cipher = SSL_CIPHER_find(s, tls13_aes128gcmsha256_id);
            if (cipher == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA,
                         ERR_R_INTERNAL_ERROR);
                return EXT_RETURN_FAIL;
            }

            psksess = SSL_SESSION_new();
            if (psksess == NULL
                    || !SSL_SESSION_set1_master_key(psksess, psk, psklen)
                    || !SSL_SESSION_set_cipher(psksess, cipher)
                    || !SSL_SESSION_set_protocol_version(psksess, TLS1_3_VERSION)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA,
                         ERR_R_INTERNAL_ERROR);
                OPENSSL_cleanse(psk, psklen);
                return EXT_RETURN_FAIL;
            }
            OPENSSL_cleanse(psk, psklen);
        }
    }
#endif  /* OPENSSL_NO_PSK */

    SSL_SESSION_free(s->psksession);
    s->psksession = psksess;
    if (psksess != NULL) {
        OPENSSL_free(s->psksession_id);
        s->psksession_id = OPENSSL_memdup(id, idlen);
        if (s->psksession_id == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA, ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
        s->psksession_id_len = idlen;
    }

    if (s->early_data_state != SSL_EARLY_DATA_CONNECTING
            || (s->session->ext.max_early_data == 0
                && (psksess == NULL || psksess->ext.max_early_data == 0))) {
        s->max_early_data = 0;
        return EXT_RETURN_NOT_SENT;
    }
    edsess = s->session->ext.max_early_data != 0 ? s->session : psksess;
    s->max_early_data = edsess->ext.max_early_data;

    if (edsess->ext.hostname != NULL) {
        if (s->ext.hostname == NULL
                || (s->ext.hostname != NULL
                    && strcmp(s->ext.hostname, edsess->ext.hostname) != 0)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA,
                     SSL_R_INCONSISTENT_EARLY_DATA_SNI);
            return EXT_RETURN_FAIL;
        }
    }

    if ((s->ext.alpn == NULL && edsess->ext.alpn_selected != NULL)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA,
                 SSL_R_INCONSISTENT_EARLY_DATA_ALPN);
        return EXT_RETURN_FAIL;
    }

    /*
     * Verify that we are offering an ALPN protocol consistent with the early
     * data.
     */
    if (edsess->ext.alpn_selected != NULL) {
        PACKET prots, alpnpkt;
        int found = 0;

        if (!PACKET_buf_init(&prots, s->ext.alpn, s->ext.alpn_len)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA, ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
        while (PACKET_get_length_prefixed_1(&prots, &alpnpkt)) {
            if (PACKET_equal(&alpnpkt, edsess->ext.alpn_selected,
                             edsess->ext.alpn_selected_len)) {
                found = 1;
                break;
            }
        }
        if (!found) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA,
                     SSL_R_INCONSISTENT_EARLY_DATA_ALPN);
            return EXT_RETURN_FAIL;
        }
    }

    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_early_data)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_EARLY_DATA,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    /*
     * We set this to rejected here. Later, if the server acknowledges the
     * extension, we set it to accepted.
     */
    s->ext.early_data = SSL_EARLY_DATA_REJECTED;
    s->ext.early_data_ok = 1;

    return EXT_RETURN_SENT;
}