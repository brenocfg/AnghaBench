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

/* Variables and functions */
#define  TLSEXT_TYPE_application_layer_protocol_negotiation 151 
#define  TLSEXT_TYPE_certificate_authorities 150 
#define  TLSEXT_TYPE_cookie 149 
#define  TLSEXT_TYPE_early_data 148 
#define  TLSEXT_TYPE_ec_point_formats 147 
#define  TLSEXT_TYPE_encrypt_then_mac 146 
#define  TLSEXT_TYPE_extended_master_secret 145 
#define  TLSEXT_TYPE_key_share 144 
#define  TLSEXT_TYPE_max_fragment_length 143 
#define  TLSEXT_TYPE_next_proto_neg 142 
#define  TLSEXT_TYPE_padding 141 
#define  TLSEXT_TYPE_post_handshake_auth 140 
#define  TLSEXT_TYPE_psk 139 
#define  TLSEXT_TYPE_psk_kex_modes 138 
#define  TLSEXT_TYPE_renegotiate 137 
#define  TLSEXT_TYPE_server_name 136 
#define  TLSEXT_TYPE_session_ticket 135 
#define  TLSEXT_TYPE_signature_algorithms 134 
#define  TLSEXT_TYPE_signed_certificate_timestamp 133 
#define  TLSEXT_TYPE_srp 132 
#define  TLSEXT_TYPE_status_request 131 
#define  TLSEXT_TYPE_supported_groups 130 
#define  TLSEXT_TYPE_supported_versions 129 
#define  TLSEXT_TYPE_use_srtp 128 

int SSL_extension_supported(unsigned int ext_type)
{
    switch (ext_type) {
        /* Internally supported extensions. */
    case TLSEXT_TYPE_application_layer_protocol_negotiation:
#ifndef OPENSSL_NO_EC
    case TLSEXT_TYPE_ec_point_formats:
    case TLSEXT_TYPE_supported_groups:
    case TLSEXT_TYPE_key_share:
#endif
#ifndef OPENSSL_NO_NEXTPROTONEG
    case TLSEXT_TYPE_next_proto_neg:
#endif
    case TLSEXT_TYPE_padding:
    case TLSEXT_TYPE_renegotiate:
    case TLSEXT_TYPE_max_fragment_length:
    case TLSEXT_TYPE_server_name:
    case TLSEXT_TYPE_session_ticket:
    case TLSEXT_TYPE_signature_algorithms:
#ifndef OPENSSL_NO_SRP
    case TLSEXT_TYPE_srp:
#endif
#ifndef OPENSSL_NO_OCSP
    case TLSEXT_TYPE_status_request:
#endif
#ifndef OPENSSL_NO_CT
    case TLSEXT_TYPE_signed_certificate_timestamp:
#endif
#ifndef OPENSSL_NO_SRTP
    case TLSEXT_TYPE_use_srtp:
#endif
    case TLSEXT_TYPE_encrypt_then_mac:
    case TLSEXT_TYPE_supported_versions:
    case TLSEXT_TYPE_extended_master_secret:
    case TLSEXT_TYPE_psk_kex_modes:
    case TLSEXT_TYPE_cookie:
    case TLSEXT_TYPE_early_data:
    case TLSEXT_TYPE_certificate_authorities:
    case TLSEXT_TYPE_psk:
    case TLSEXT_TYPE_post_handshake_auth:
        return 1;
    default:
        return 0;
    }
}