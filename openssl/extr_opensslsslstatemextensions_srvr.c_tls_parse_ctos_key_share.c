#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_10__ {unsigned int group_id; int /*<<< orphan*/ * peer_tmp; } ;
struct TYPE_9__ {int psk_kex_mode; } ;
struct TYPE_11__ {TYPE_2__ s3; TYPE_1__ ext; scalar_t__ hit; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_PKEY_set1_tls_encodedpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_MISSING_EXTENSION ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_KEY_SHARE ; 
 int /*<<< orphan*/  SSL_R_BAD_ECPOINT ; 
 int /*<<< orphan*/  SSL_R_BAD_KEY_SHARE ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_MISSING_SUPPORTED_GROUPS_EXTENSION ; 
 int /*<<< orphan*/  SSL_R_UNABLE_TO_FIND_ECDH_PARAMETERS ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLSEXT_KEX_MODE_FLAG_KE_DHE ; 
 int /*<<< orphan*/  check_in_list (TYPE_3__*,unsigned int,int /*<<< orphan*/  const*,size_t,int) ; 
 int /*<<< orphan*/ * ssl_generate_param_group (unsigned int) ; 
 int /*<<< orphan*/  tls1_get_peer_groups (TYPE_3__*,int /*<<< orphan*/  const**,size_t*) ; 
 int /*<<< orphan*/  tls1_get_supported_groups (TYPE_3__*,int /*<<< orphan*/  const**,size_t*) ; 

int tls_parse_ctos_key_share(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                             size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    unsigned int group_id;
    PACKET key_share_list, encoded_pt;
    const uint16_t *clntgroups, *srvrgroups;
    size_t clnt_num_groups, srvr_num_groups;
    int found = 0;

    if (s->hit && (s->ext.psk_kex_mode & TLSEXT_KEX_MODE_FLAG_KE_DHE) == 0)
        return 1;

    /* Sanity check */
    if (s->s3.peer_tmp != NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_KEY_SHARE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (!PACKET_as_length_prefixed_2(pkt, &key_share_list)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_KEY_SHARE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    /* Get our list of supported groups */
    tls1_get_supported_groups(s, &srvrgroups, &srvr_num_groups);
    /* Get the clients list of supported groups. */
    tls1_get_peer_groups(s, &clntgroups, &clnt_num_groups);
    if (clnt_num_groups == 0) {
        /*
         * This can only happen if the supported_groups extension was not sent,
         * because we verify that the length is non-zero when we process that
         * extension.
         */
        SSLfatal(s, SSL_AD_MISSING_EXTENSION, SSL_F_TLS_PARSE_CTOS_KEY_SHARE,
                 SSL_R_MISSING_SUPPORTED_GROUPS_EXTENSION);
        return 0;
    }

    if (s->s3.group_id != 0 && PACKET_remaining(&key_share_list) == 0) {
        /*
         * If we set a group_id already, then we must have sent an HRR
         * requesting a new key_share. If we haven't got one then that is an
         * error
         */
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_CTOS_KEY_SHARE,
                 SSL_R_BAD_KEY_SHARE);
        return 0;
    }

    while (PACKET_remaining(&key_share_list) > 0) {
        if (!PACKET_get_net_2(&key_share_list, &group_id)
                || !PACKET_get_length_prefixed_2(&key_share_list, &encoded_pt)
                || PACKET_remaining(&encoded_pt) == 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_KEY_SHARE,
                     SSL_R_LENGTH_MISMATCH);
            return 0;
        }

        /*
         * If we already found a suitable key_share we loop through the
         * rest to verify the structure, but don't process them.
         */
        if (found)
            continue;

        /*
         * If we sent an HRR then the key_share sent back MUST be for the group
         * we requested, and must be the only key_share sent.
         */
        if (s->s3.group_id != 0
                && (group_id != s->s3.group_id
                    || PACKET_remaining(&key_share_list) != 0)) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                     SSL_F_TLS_PARSE_CTOS_KEY_SHARE, SSL_R_BAD_KEY_SHARE);
            return 0;
        }

        /* Check if this share is in supported_groups sent from client */
        if (!check_in_list(s, group_id, clntgroups, clnt_num_groups, 0)) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                     SSL_F_TLS_PARSE_CTOS_KEY_SHARE, SSL_R_BAD_KEY_SHARE);
            return 0;
        }

        /* Check if this share is for a group we can use */
        if (!check_in_list(s, group_id, srvrgroups, srvr_num_groups, 1)) {
            /* Share not suitable */
            continue;
        }

        if ((s->s3.peer_tmp = ssl_generate_param_group(group_id)) == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_KEY_SHARE,
                   SSL_R_UNABLE_TO_FIND_ECDH_PARAMETERS);
            return 0;
        }

        s->s3.group_id = group_id;

        if (!EVP_PKEY_set1_tls_encodedpoint(s->s3.peer_tmp,
                PACKET_data(&encoded_pt),
                PACKET_remaining(&encoded_pt))) {
            SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                     SSL_F_TLS_PARSE_CTOS_KEY_SHARE, SSL_R_BAD_ECPOINT);
            return 0;
        }

        found = 1;
    }
#endif

    return 1;
}