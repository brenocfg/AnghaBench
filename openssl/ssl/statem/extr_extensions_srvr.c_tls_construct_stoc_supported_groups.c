#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_9__ {scalar_t__ group_id; } ;
struct TYPE_10__ {TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_STOC_SUPPORTED_GROUPS ; 
 int /*<<< orphan*/  SSL_SECOP_CURVE_SUPPORTED ; 
 int /*<<< orphan*/  SSL_version (TYPE_2__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLSEXT_TYPE_supported_groups ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls1_get_supported_groups (TYPE_2__*,scalar_t__ const**,size_t*) ; 
 scalar_t__ tls_group_allowed (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_valid_group (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

EXT_RETURN tls_construct_stoc_supported_groups(SSL *s, WPACKET *pkt,
                                               unsigned int context, X509 *x,
                                               size_t chainidx)
{
    const uint16_t *groups;
    size_t numgroups, i, first = 1;

    /* s->s3.group_id is non zero if we accepted a key_share */
    if (s->s3.group_id == 0)
        return EXT_RETURN_NOT_SENT;

    /* Get our list of supported groups */
    tls1_get_supported_groups(s, &groups, &numgroups);
    if (numgroups == 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_STOC_SUPPORTED_GROUPS, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    /* Copy group ID if supported */
    for (i = 0; i < numgroups; i++) {
        uint16_t group = groups[i];

        if (tls_valid_group(s, group, SSL_version(s))
                && tls_group_allowed(s, group, SSL_SECOP_CURVE_SUPPORTED)) {
            if (first) {
                /*
                 * Check if the client is already using our preferred group. If
                 * so we don't need to add this extension
                 */
                if (s->s3.group_id == group)
                    return EXT_RETURN_NOT_SENT;

                /* Add extension header */
                if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_supported_groups)
                           /* Sub-packet for supported_groups extension */
                        || !WPACKET_start_sub_packet_u16(pkt)
                        || !WPACKET_start_sub_packet_u16(pkt)) {
                    SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                             SSL_F_TLS_CONSTRUCT_STOC_SUPPORTED_GROUPS,
                             ERR_R_INTERNAL_ERROR);
                    return EXT_RETURN_FAIL;
                }

                first = 0;
            }
            if (!WPACKET_put_bytes_u16(pkt, group)) {
                    SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                             SSL_F_TLS_CONSTRUCT_STOC_SUPPORTED_GROUPS,
                             ERR_R_INTERNAL_ERROR);
                    return EXT_RETURN_FAIL;
                }
        }
    }

    if (!WPACKET_close(pkt) || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_STOC_SUPPORTED_GROUPS,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}