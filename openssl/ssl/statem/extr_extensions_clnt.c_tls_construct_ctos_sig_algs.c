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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_CLIENT_USE_SIGALGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_SIG_ALGS ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_signature_algorithms ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls12_copy_sigalgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t tls12_get_psigalgs (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 

EXT_RETURN tls_construct_ctos_sig_algs(SSL *s, WPACKET *pkt,
                                       unsigned int context, X509 *x,
                                       size_t chainidx)
{
    size_t salglen;
    const uint16_t *salg;

    if (!SSL_CLIENT_USE_SIGALGS(s))
        return EXT_RETURN_NOT_SENT;

    salglen = tls12_get_psigalgs(s, 1, &salg);
    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_signature_algorithms)
               /* Sub-packet for sig-algs extension */
            || !WPACKET_start_sub_packet_u16(pkt)
               /* Sub-packet for the actual list */
            || !WPACKET_start_sub_packet_u16(pkt)
            || !tls12_copy_sigalgs(s, pkt, salg, salglen)
            || !WPACKET_close(pkt)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CTOS_SIG_ALGS,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}