#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {scalar_t__ hello_retry_request; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_EARLY_DATA ; 
 scalar_t__ SSL_HRR_NONE ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_parse_ctos_early_data(SSL *s, PACKET *pkt, unsigned int context,
                              X509 *x, size_t chainidx)
{
    if (PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PARSE_CTOS_EARLY_DATA, SSL_R_BAD_EXTENSION);
        return 0;
    }

    if (s->hello_retry_request != SSL_HRR_NONE) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER,
                 SSL_F_TLS_PARSE_CTOS_EARLY_DATA, SSL_R_BAD_EXTENSION);
        return 0;
    }

    return 1;
}