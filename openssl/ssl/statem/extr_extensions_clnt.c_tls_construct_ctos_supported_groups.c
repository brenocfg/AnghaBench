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
 int ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_SUPPORTED_GROUPS ; 
 int /*<<< orphan*/  SSL_SECOP_CURVE_SUPPORTED ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLSEXT_TYPE_supported_groups ; 
 int /*<<< orphan*/  WPACKET_FLAGS_NON_ZERO_LENGTH ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int ssl_get_min_max_version (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls1_get_supported_groups (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t*) ; 
 scalar_t__ tls_group_allowed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_valid_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  use_ecc (int /*<<< orphan*/ *,int) ; 

EXT_RETURN tls_construct_ctos_supported_groups(SSL *s, WPACKET *pkt,
                                               unsigned int context, X509 *x,
                                               size_t chainidx)
{
    const uint16_t *pgroups = NULL;
    size_t num_groups = 0, i;
    int min_version, max_version, reason;

    reason = ssl_get_min_max_version(s, &min_version, &max_version, NULL);
    if (reason != 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_SUPPORTED_GROUPS, reason);
        return EXT_RETURN_FAIL;
    }

#if defined(OPENSSL_NO_EC)
    if (max_version < TLS1_3_VERSION)
        return EXT_RETURN_NOT_SENT;
#else
    if (!use_ecc(s, max_version) && max_version < TLS1_3_VERSION)
        return EXT_RETURN_NOT_SENT;
#endif

    /*
     * Add TLS extension supported_groups to the ClientHello message
     */
    tls1_get_supported_groups(s, &pgroups, &num_groups);

    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_supported_groups)
               /* Sub-packet for supported_groups extension */
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_set_flags(pkt, WPACKET_FLAGS_NON_ZERO_LENGTH)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_SUPPORTED_GROUPS,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }
    /* Copy group ID if supported */
    for (i = 0; i < num_groups; i++) {
        uint16_t ctmp = pgroups[i];

        if (tls_valid_group(s, ctmp, max_version)
                && tls_group_allowed(s, ctmp, SSL_SECOP_CURVE_SUPPORTED)) {
            if (!WPACKET_put_bytes_u16(pkt, ctmp)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_CTOS_SUPPORTED_GROUPS,
                         ERR_R_INTERNAL_ERROR);
                return EXT_RETURN_FAIL;
            }
        }
    }
    if (!WPACKET_close(pkt) || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_SUPPORTED_GROUPS,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}