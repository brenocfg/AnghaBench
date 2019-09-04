#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_10__ {scalar_t__ early_data_ok; int /*<<< orphan*/ * hostname; } ;
struct TYPE_11__ {int servername_done; TYPE_3__ ext; TYPE_2__* session; scalar_t__ hit; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hostname; } ;
struct TYPE_9__ {TYPE_1__ ext; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_contains_zero_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_strndup (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_UNRECOGNIZED_NAME ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_SERVER_NAME ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLSEXT_MAXLEN_host_name ; 
 unsigned int TLSEXT_NAMETYPE_host_name ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

int tls_parse_ctos_server_name(SSL *s, PACKET *pkt, unsigned int context,
                               X509 *x, size_t chainidx)
{
    unsigned int servname_type;
    PACKET sni, hostname;

    if (!PACKET_as_length_prefixed_2(pkt, &sni)
        /* ServerNameList must be at least 1 byte long. */
        || PACKET_remaining(&sni) == 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_SERVER_NAME,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    /*
     * Although the intent was for server_name to be extensible, RFC 4366
     * was not clear about it; and so OpenSSL among other implementations,
     * always and only allows a 'host_name' name types.
     * RFC 6066 corrected the mistake but adding new name types
     * is nevertheless no longer feasible, so act as if no other
     * SNI types can exist, to simplify parsing.
     *
     * Also note that the RFC permits only one SNI value per type,
     * i.e., we can only have a single hostname.
     */
    if (!PACKET_get_1(&sni, &servname_type)
        || servname_type != TLSEXT_NAMETYPE_host_name
        || !PACKET_as_length_prefixed_2(&sni, &hostname)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_SERVER_NAME,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    if (!s->hit || SSL_IS_TLS13(s)) {
        if (PACKET_remaining(&hostname) > TLSEXT_MAXLEN_host_name) {
            SSLfatal(s, SSL_AD_UNRECOGNIZED_NAME,
                     SSL_F_TLS_PARSE_CTOS_SERVER_NAME,
                     SSL_R_BAD_EXTENSION);
            return 0;
        }

        if (PACKET_contains_zero_byte(&hostname)) {
            SSLfatal(s, SSL_AD_UNRECOGNIZED_NAME,
                     SSL_F_TLS_PARSE_CTOS_SERVER_NAME,
                     SSL_R_BAD_EXTENSION);
            return 0;
        }

        /*
         * Store the requested SNI in the SSL as temporary storage.
         * If we accept it, it will get stored in the SSL_SESSION as well.
         */
        OPENSSL_free(s->ext.hostname);
        s->ext.hostname = NULL;
        if (!PACKET_strndup(&hostname, &s->ext.hostname)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_SERVER_NAME,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }

        s->servername_done = 1;
    }
    if (s->hit) {
        /*
         * TODO(openssl-team): if the SNI doesn't match, we MUST
         * fall back to a full handshake.
         */
        s->servername_done = (s->session->ext.hostname != NULL)
            && PACKET_equal(&hostname, s->session->ext.hostname,
                            strlen(s->session->ext.hostname));

        if (!s->servername_done && s->session->ext.hostname != NULL)
            s->ext.early_data_ok = 0;
    }

    return 1;
}