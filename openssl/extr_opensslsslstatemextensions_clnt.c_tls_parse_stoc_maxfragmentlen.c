#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_9__ {unsigned int max_fragment_len_mode; } ;
struct TYPE_10__ {TYPE_2__* session; TYPE_3__ ext; } ;
struct TYPE_7__ {unsigned int max_fragment_len_mode; } ;
struct TYPE_8__ {TYPE_1__ ext; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MAX_FRAGMENT_LENGTH_EXT_VALID (unsigned int) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_MAXFRAGMENTLEN ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSL_R_SSL3_EXT_INVALID_MAX_FRAGMENT_LENGTH ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_stoc_maxfragmentlen(SSL *s, PACKET *pkt, unsigned int context,
                                  X509 *x, size_t chainidx)
{
    unsigned int value;

    if (PACKET_remaining(pkt) != 1 || !PACKET_get_1(pkt, &value)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_MAXFRAGMENTLEN,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }

    /* |value| should contains a valid max-fragment-length code. */
    if (!IS_MAX_FRAGMENT_LENGTH_EXT_VALID(value)) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                 SSL_F_TLS_PARSE_STOC_MAXFRAGMENTLEN,
                 SSL_R_SSL3_EXT_INVALID_MAX_FRAGMENT_LENGTH);
        return 0;
    }

    /* Must be the same value as client-configured one who was sent to server */
    /*-
     * RFC 6066: if a client receives a maximum fragment length negotiation
     * response that differs from the length it requested, ...
     * It must abort with SSL_AD_ILLEGAL_PARAMETER alert
     */
    if (value != s->ext.max_fragment_len_mode) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                 SSL_F_TLS_PARSE_STOC_MAXFRAGMENTLEN,
                 SSL_R_SSL3_EXT_INVALID_MAX_FRAGMENT_LENGTH);
        return 0;
    }

    /*
     * Maximum Fragment Length Negotiation succeeded.
     * The negotiated Maximum Fragment Length is binding now.
     */
    s->session->ext.max_fragment_len_mode = value;

    return 1;
}