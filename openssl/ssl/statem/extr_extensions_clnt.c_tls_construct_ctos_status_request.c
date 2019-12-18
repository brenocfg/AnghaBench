#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_6__ {scalar_t__ exts; int /*<<< orphan*/  ids; } ;
struct TYPE_7__ {scalar_t__ status_type; TYPE_1__ ocsp; } ;
struct TYPE_8__ {TYPE_2__ ext; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  OCSP_RESPID ;
typedef  int /*<<< orphan*/  EXT_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EXT_RETURN_FAIL ; 
 int /*<<< orphan*/  EXT_RETURN_NOT_SENT ; 
 int /*<<< orphan*/  EXT_RETURN_SENT ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CTOS_STATUS_REQUEST ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLSEXT_STATUSTYPE_ocsp ; 
 int /*<<< orphan*/  TLSEXT_TYPE_status_request ; 
 int /*<<< orphan*/  WPACKET_allocate_bytes (int /*<<< orphan*/ *,int,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_allocate_bytes_u16 (int /*<<< orphan*/ *,int,unsigned char**) ; 
 int i2d_OCSP_RESPID (int /*<<< orphan*/ *,unsigned char**) ; 
 int i2d_X509_EXTENSIONS (scalar_t__,unsigned char**) ; 
 int sk_OCSP_RESPID_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_OCSP_RESPID_value (int /*<<< orphan*/ ,int) ; 

EXT_RETURN tls_construct_ctos_status_request(SSL *s, WPACKET *pkt,
                                             unsigned int context, X509 *x,
                                             size_t chainidx)
{
    int i;

    /* This extension isn't defined for client Certificates */
    if (x != NULL)
        return EXT_RETURN_NOT_SENT;

    if (s->ext.status_type != TLSEXT_STATUSTYPE_ocsp)
        return EXT_RETURN_NOT_SENT;

    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_status_request)
               /* Sub-packet for status request extension */
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_put_bytes_u8(pkt, TLSEXT_STATUSTYPE_ocsp)
               /* Sub-packet for the ids */
            || !WPACKET_start_sub_packet_u16(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_STATUS_REQUEST, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }
    for (i = 0; i < sk_OCSP_RESPID_num(s->ext.ocsp.ids); i++) {
        unsigned char *idbytes;
        OCSP_RESPID *id = sk_OCSP_RESPID_value(s->ext.ocsp.ids, i);
        int idlen = i2d_OCSP_RESPID(id, NULL);

        if (idlen <= 0
                   /* Sub-packet for an individual id */
                || !WPACKET_sub_allocate_bytes_u16(pkt, idlen, &idbytes)
                || i2d_OCSP_RESPID(id, &idbytes) != idlen) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CTOS_STATUS_REQUEST,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
    }
    if (!WPACKET_close(pkt)
            || !WPACKET_start_sub_packet_u16(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_STATUS_REQUEST, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }
    if (s->ext.ocsp.exts) {
        unsigned char *extbytes;
        int extlen = i2d_X509_EXTENSIONS(s->ext.ocsp.exts, NULL);

        if (extlen < 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CTOS_STATUS_REQUEST,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
        }
        if (!WPACKET_allocate_bytes(pkt, extlen, &extbytes)
                || i2d_X509_EXTENSIONS(s->ext.ocsp.exts, &extbytes)
                   != extlen) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CTOS_STATUS_REQUEST,
                     ERR_R_INTERNAL_ERROR);
            return EXT_RETURN_FAIL;
       }
    }
    if (!WPACKET_close(pkt) || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CTOS_STATUS_REQUEST, ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    return EXT_RETURN_SENT;
}