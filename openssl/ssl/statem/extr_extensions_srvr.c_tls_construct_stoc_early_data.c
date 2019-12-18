#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_5__ {scalar_t__ early_data; } ;
struct TYPE_6__ {scalar_t__ max_early_data; TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 scalar_t__ SSL_EARLY_DATA_ACCEPTED ; 
 unsigned int SSL_EXT_TLS1_3_NEW_SESSION_TICKET ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_STOC_EARLY_DATA ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_early_data ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 

EXT_RETURN tls_construct_stoc_early_data(SSL *s, WPACKET *pkt,
                                         unsigned int context, X509 *x,
                                         size_t chainidx)
{
    if (context == SSL_EXT_TLS1_3_NEW_SESSION_TICKET) {
        if (s->max_early_data == 0)
            return EXT_RETURN_NOT_SENT;

        if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_early_data)
                || !WPACKET_start_sub_packet_u16(pkt)
                || !WPACKET_put_bytes_u32(pkt, s->max_early_data)
                || !WPACKET_close(pkt)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_STOC_EARLY_DATA, ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }

        return EXT_RETURN_SENT;
    }

    if (s->ext.early_data != SSL_EARLY_DATA_ACCEPTED)
        return EXT_RETURN_NOT_SENT;

    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_early_data)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_EARLY_DATA,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}