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
#define  SSL3_AD_BAD_CERTIFICATE 158 
#define  SSL3_AD_BAD_RECORD_MAC 157 
#define  SSL3_AD_CERTIFICATE_EXPIRED 156 
#define  SSL3_AD_CERTIFICATE_REVOKED 155 
#define  SSL3_AD_CERTIFICATE_UNKNOWN 154 
#define  SSL3_AD_CLOSE_NOTIFY 153 
#define  SSL3_AD_DECOMPRESSION_FAILURE 152 
#define  SSL3_AD_HANDSHAKE_FAILURE 151 
#define  SSL3_AD_ILLEGAL_PARAMETER 150 
#define  SSL3_AD_NO_CERTIFICATE 149 
#define  SSL3_AD_UNEXPECTED_MESSAGE 148 
#define  SSL3_AD_UNSUPPORTED_CERTIFICATE 147 
#define  TLS1_AD_ACCESS_DENIED 146 
#define  TLS1_AD_BAD_CERTIFICATE_HASH_VALUE 145 
#define  TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE 144 
#define  TLS1_AD_CERTIFICATE_UNOBTAINABLE 143 
#define  TLS1_AD_DECODE_ERROR 142 
#define  TLS1_AD_DECRYPTION_FAILED 141 
#define  TLS1_AD_DECRYPT_ERROR 140 
#define  TLS1_AD_EXPORT_RESTRICTION 139 
#define  TLS1_AD_INSUFFICIENT_SECURITY 138 
#define  TLS1_AD_INTERNAL_ERROR 137 
#define  TLS1_AD_NO_APPLICATION_PROTOCOL 136 
#define  TLS1_AD_NO_RENEGOTIATION 135 
#define  TLS1_AD_PROTOCOL_VERSION 134 
#define  TLS1_AD_RECORD_OVERFLOW 133 
#define  TLS1_AD_UNKNOWN_CA 132 
#define  TLS1_AD_UNKNOWN_PSK_IDENTITY 131 
#define  TLS1_AD_UNRECOGNIZED_NAME 130 
#define  TLS1_AD_UNSUPPORTED_EXTENSION 129 
#define  TLS1_AD_USER_CANCELLED 128 

const char *SSL_alert_desc_string_long(int value)
{
    switch (value & 0xff) {
    case SSL3_AD_CLOSE_NOTIFY:
        return "close notify";
    case SSL3_AD_UNEXPECTED_MESSAGE:
        return "unexpected_message";
    case SSL3_AD_BAD_RECORD_MAC:
        return "bad record mac";
    case SSL3_AD_DECOMPRESSION_FAILURE:
        return "decompression failure";
    case SSL3_AD_HANDSHAKE_FAILURE:
        return "handshake failure";
    case SSL3_AD_NO_CERTIFICATE:
        return "no certificate";
    case SSL3_AD_BAD_CERTIFICATE:
        return "bad certificate";
    case SSL3_AD_UNSUPPORTED_CERTIFICATE:
        return "unsupported certificate";
    case SSL3_AD_CERTIFICATE_REVOKED:
        return "certificate revoked";
    case SSL3_AD_CERTIFICATE_EXPIRED:
        return "certificate expired";
    case SSL3_AD_CERTIFICATE_UNKNOWN:
        return "certificate unknown";
    case SSL3_AD_ILLEGAL_PARAMETER:
        return "illegal parameter";
    case TLS1_AD_DECRYPTION_FAILED:
        return "decryption failed";
    case TLS1_AD_RECORD_OVERFLOW:
        return "record overflow";
    case TLS1_AD_UNKNOWN_CA:
        return "unknown CA";
    case TLS1_AD_ACCESS_DENIED:
        return "access denied";
    case TLS1_AD_DECODE_ERROR:
        return "decode error";
    case TLS1_AD_DECRYPT_ERROR:
        return "decrypt error";
    case TLS1_AD_EXPORT_RESTRICTION:
        return "export restriction";
    case TLS1_AD_PROTOCOL_VERSION:
        return "protocol version";
    case TLS1_AD_INSUFFICIENT_SECURITY:
        return "insufficient security";
    case TLS1_AD_INTERNAL_ERROR:
        return "internal error";
    case TLS1_AD_USER_CANCELLED:
        return "user canceled";
    case TLS1_AD_NO_RENEGOTIATION:
        return "no renegotiation";
    case TLS1_AD_UNSUPPORTED_EXTENSION:
        return "unsupported extension";
    case TLS1_AD_CERTIFICATE_UNOBTAINABLE:
        return "certificate unobtainable";
    case TLS1_AD_UNRECOGNIZED_NAME:
        return "unrecognized name";
    case TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE:
        return "bad certificate status response";
    case TLS1_AD_BAD_CERTIFICATE_HASH_VALUE:
        return "bad certificate hash value";
    case TLS1_AD_UNKNOWN_PSK_IDENTITY:
        return "unknown PSK identity";
    case TLS1_AD_NO_APPLICATION_PROTOCOL:
        return "no application protocol";
    default:
        return "unknown";
    }
}