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
typedef  int /*<<< orphan*/  WPACKET ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  CERT_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_OUTPUT_CERT_CHAIN ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_add_cert_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

unsigned long ssl3_output_cert_chain(SSL *s, WPACKET *pkt, CERT_PKEY *cpk)
{
    if (!WPACKET_start_sub_packet_u24(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_OUTPUT_CERT_CHAIN,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (!ssl_add_cert_chain(s, pkt, cpk))
        return 0;

    if (!WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_OUTPUT_CERT_CHAIN,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    return 1;
}