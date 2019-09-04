#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CERTIFICATE_AUTHORITIES ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_ca_names (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tls_parse_certificate_authorities(SSL *s, PACKET *pkt,
                                             unsigned int context, X509 *x,
                                             size_t chainidx)
{
    if (!parse_ca_names(s, pkt))
        return 0;
    if (PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PARSE_CERTIFICATE_AUTHORITIES, SSL_R_BAD_EXTENSION);
        return 0;
    }
    return 1;
}