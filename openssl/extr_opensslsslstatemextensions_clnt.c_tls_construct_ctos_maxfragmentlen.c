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
struct TYPE_5__ {scalar_t__ max_fragment_len_mode; } ;
struct TYPE_6__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_MAXFRAGMENTLEN ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_TYPE_max_fragment_length ; 
 scalar_t__ TLSEXT_max_fragment_length_DISABLED ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 

EXT_RETURN tls_construct_ctos_maxfragmentlen(SSL *s, WPACKET *pkt,
                                             unsigned int context, X509 *x,
                                             size_t chainidx)
{
    if (s->ext.max_fragment_len_mode == TLSEXT_max_fragment_length_DISABLED)
        return EXT_RETURN_NOT_SENT;

    /* Add Max Fragment Length extension if client enabled it. */
    /*-
     * 4 bytes for this extension type and extension length
     * 1 byte for the Max Fragment Length code value.
     */
    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_max_fragment_length)
            /* Sub-packet for Max Fragment Length extension (1 byte) */
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_put_bytes_u8(pkt, s->ext.max_fragment_len_mode)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_MAXFRAGMENTLEN, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}