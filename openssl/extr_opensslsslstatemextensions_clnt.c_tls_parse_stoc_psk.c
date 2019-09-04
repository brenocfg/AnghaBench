#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_7__ {scalar_t__ max_early_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  early_secret; TYPE_1__ ext; } ;
struct TYPE_8__ {int tick_identity; scalar_t__ early_data_ok; } ;
struct TYPE_9__ {int hit; scalar_t__ early_data_state; TYPE_2__ ext; TYPE_6__* psksession; TYPE_6__* session; int /*<<< orphan*/  early_secret; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 scalar_t__ SSL_EARLY_DATA_FINISHED_WRITING ; 
 scalar_t__ SSL_EARLY_DATA_WRITE_RETRY ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_PSK ; 
 int /*<<< orphan*/  SSL_R_BAD_PSK_IDENTITY ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_6__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_stoc_psk(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                       size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    unsigned int identity;

    if (!PACKET_get_net_2(pkt, &identity) || PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_PSK,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    if (identity >= (unsigned int)s->ext.tick_identity) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_STOC_PSK,
                 SSL_R_BAD_PSK_IDENTITY);
        return 0;
    }

    /*
     * Session resumption tickets are always sent before PSK tickets. If the
     * ticket index is 0 then it must be for a session resumption ticket if we
     * sent two tickets, or if we didn't send a PSK ticket.
     */
    if (identity == 0 && (s->psksession == NULL || s->ext.tick_identity == 2)) {
        s->hit = 1;
        SSL_SESSION_free(s->psksession);
        s->psksession = NULL;
        return 1;
    }

    if (s->psksession == NULL) {
        /* Should never happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_PSK,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /*
     * If we used the external PSK for sending early_data then s->early_secret
     * is already set up, so don't overwrite it. Otherwise we copy the
     * early_secret across that we generated earlier.
     */
    if ((s->early_data_state != SSL_EARLY_DATA_WRITE_RETRY
                && s->early_data_state != SSL_EARLY_DATA_FINISHED_WRITING)
            || s->session->ext.max_early_data > 0
            || s->psksession->ext.max_early_data == 0)
        memcpy(s->early_secret, s->psksession->early_secret, EVP_MAX_MD_SIZE);

    SSL_SESSION_free(s->session);
    s->session = s->psksession;
    s->psksession = NULL;
    s->hit = 1;
    /* Early data is only allowed if we used the first ticket */
    if (identity != 0)
        s->ext.early_data_ok = 0;
#endif

    return 1;
}