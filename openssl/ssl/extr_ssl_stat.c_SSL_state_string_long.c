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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
#define  DTLS_ST_CR_HELLO_VERIFY_REQUEST 177 
#define  DTLS_ST_SW_HELLO_VERIFY_REQUEST 176 
 int SSL_get_state (int /*<<< orphan*/  const*) ; 
#define  TLS_ST_BEFORE 175 
#define  TLS_ST_CR_CERT 174 
#define  TLS_ST_CR_CERT_REQ 173 
#define  TLS_ST_CR_CERT_STATUS 172 
#define  TLS_ST_CR_CERT_VRFY 171 
#define  TLS_ST_CR_CHANGE 170 
#define  TLS_ST_CR_ENCRYPTED_EXTENSIONS 169 
#define  TLS_ST_CR_FINISHED 168 
#define  TLS_ST_CR_HELLO_REQ 167 
#define  TLS_ST_CR_KEY_EXCH 166 
#define  TLS_ST_CR_KEY_UPDATE 165 
#define  TLS_ST_CR_SESSION_TICKET 164 
#define  TLS_ST_CR_SRVR_DONE 163 
#define  TLS_ST_CR_SRVR_HELLO 162 
#define  TLS_ST_CW_CERT 161 
#define  TLS_ST_CW_CERT_VRFY 160 
#define  TLS_ST_CW_CHANGE 159 
#define  TLS_ST_CW_CLNT_HELLO 158 
#define  TLS_ST_CW_END_OF_EARLY_DATA 157 
#define  TLS_ST_CW_FINISHED 156 
#define  TLS_ST_CW_KEY_EXCH 155 
#define  TLS_ST_CW_KEY_UPDATE 154 
#define  TLS_ST_CW_NEXT_PROTO 153 
#define  TLS_ST_EARLY_DATA 152 
#define  TLS_ST_OK 151 
#define  TLS_ST_PENDING_EARLY_DATA_END 150 
#define  TLS_ST_SR_CERT 149 
#define  TLS_ST_SR_CERT_VRFY 148 
#define  TLS_ST_SR_CHANGE 147 
#define  TLS_ST_SR_CLNT_HELLO 146 
#define  TLS_ST_SR_END_OF_EARLY_DATA 145 
#define  TLS_ST_SR_FINISHED 144 
#define  TLS_ST_SR_KEY_EXCH 143 
#define  TLS_ST_SR_KEY_UPDATE 142 
#define  TLS_ST_SR_NEXT_PROTO 141 
#define  TLS_ST_SW_CERT 140 
#define  TLS_ST_SW_CERT_REQ 139 
#define  TLS_ST_SW_CERT_STATUS 138 
#define  TLS_ST_SW_CERT_VRFY 137 
#define  TLS_ST_SW_CHANGE 136 
#define  TLS_ST_SW_ENCRYPTED_EXTENSIONS 135 
#define  TLS_ST_SW_FINISHED 134 
#define  TLS_ST_SW_HELLO_REQ 133 
#define  TLS_ST_SW_KEY_EXCH 132 
#define  TLS_ST_SW_KEY_UPDATE 131 
#define  TLS_ST_SW_SESSION_TICKET 130 
#define  TLS_ST_SW_SRVR_DONE 129 
#define  TLS_ST_SW_SRVR_HELLO 128 
 scalar_t__ ossl_statem_in_error (int /*<<< orphan*/  const*) ; 

const char *SSL_state_string_long(const SSL *s)
{
    if (ossl_statem_in_error(s))
        return "error";

    switch (SSL_get_state(s)) {
    case TLS_ST_CR_CERT_STATUS:
        return "SSLv3/TLS read certificate status";
    case TLS_ST_CW_NEXT_PROTO:
        return "SSLv3/TLS write next proto";
    case TLS_ST_SR_NEXT_PROTO:
        return "SSLv3/TLS read next proto";
    case TLS_ST_SW_CERT_STATUS:
        return "SSLv3/TLS write certificate status";
    case TLS_ST_BEFORE:
        return "before SSL initialization";
    case TLS_ST_OK:
        return "SSL negotiation finished successfully";
    case TLS_ST_CW_CLNT_HELLO:
        return "SSLv3/TLS write client hello";
    case TLS_ST_CR_SRVR_HELLO:
        return "SSLv3/TLS read server hello";
    case TLS_ST_CR_CERT:
        return "SSLv3/TLS read server certificate";
    case TLS_ST_CR_KEY_EXCH:
        return "SSLv3/TLS read server key exchange";
    case TLS_ST_CR_CERT_REQ:
        return "SSLv3/TLS read server certificate request";
    case TLS_ST_CR_SESSION_TICKET:
        return "SSLv3/TLS read server session ticket";
    case TLS_ST_CR_SRVR_DONE:
        return "SSLv3/TLS read server done";
    case TLS_ST_CW_CERT:
        return "SSLv3/TLS write client certificate";
    case TLS_ST_CW_KEY_EXCH:
        return "SSLv3/TLS write client key exchange";
    case TLS_ST_CW_CERT_VRFY:
        return "SSLv3/TLS write certificate verify";
    case TLS_ST_CW_CHANGE:
    case TLS_ST_SW_CHANGE:
        return "SSLv3/TLS write change cipher spec";
    case TLS_ST_CW_FINISHED:
    case TLS_ST_SW_FINISHED:
        return "SSLv3/TLS write finished";
    case TLS_ST_CR_CHANGE:
    case TLS_ST_SR_CHANGE:
        return "SSLv3/TLS read change cipher spec";
    case TLS_ST_CR_FINISHED:
    case TLS_ST_SR_FINISHED:
        return "SSLv3/TLS read finished";
    case TLS_ST_SR_CLNT_HELLO:
        return "SSLv3/TLS read client hello";
    case TLS_ST_SW_HELLO_REQ:
        return "SSLv3/TLS write hello request";
    case TLS_ST_SW_SRVR_HELLO:
        return "SSLv3/TLS write server hello";
    case TLS_ST_SW_CERT:
        return "SSLv3/TLS write certificate";
    case TLS_ST_SW_KEY_EXCH:
        return "SSLv3/TLS write key exchange";
    case TLS_ST_SW_CERT_REQ:
        return "SSLv3/TLS write certificate request";
    case TLS_ST_SW_SESSION_TICKET:
        return "SSLv3/TLS write session ticket";
    case TLS_ST_SW_SRVR_DONE:
        return "SSLv3/TLS write server done";
    case TLS_ST_SR_CERT:
        return "SSLv3/TLS read client certificate";
    case TLS_ST_SR_KEY_EXCH:
        return "SSLv3/TLS read client key exchange";
    case TLS_ST_SR_CERT_VRFY:
        return "SSLv3/TLS read certificate verify";
    case DTLS_ST_CR_HELLO_VERIFY_REQUEST:
        return "DTLS1 read hello verify request";
    case DTLS_ST_SW_HELLO_VERIFY_REQUEST:
        return "DTLS1 write hello verify request";
    case TLS_ST_SW_ENCRYPTED_EXTENSIONS:
        return "TLSv1.3 write encrypted extensions";
    case TLS_ST_CR_ENCRYPTED_EXTENSIONS:
        return "TLSv1.3 read encrypted extensions";
    case TLS_ST_CR_CERT_VRFY:
        return "TLSv1.3 read server certificate verify";
    case TLS_ST_SW_CERT_VRFY:
        return "TLSv1.3 write server certificate verify";
    case TLS_ST_CR_HELLO_REQ:
        return "SSLv3/TLS read hello request";
    case TLS_ST_SW_KEY_UPDATE:
        return "TLSv1.3 write server key update";
    case TLS_ST_CW_KEY_UPDATE:
        return "TLSv1.3 write client key update";
    case TLS_ST_SR_KEY_UPDATE:
        return "TLSv1.3 read client key update";
    case TLS_ST_CR_KEY_UPDATE:
        return "TLSv1.3 read server key update";
    case TLS_ST_EARLY_DATA:
        return "TLSv1.3 early data";
    case TLS_ST_PENDING_EARLY_DATA_END:
        return "TLSv1.3 pending early data end";
    case TLS_ST_CW_END_OF_EARLY_DATA:
        return "TLSv1.3 write end of early data";
    case TLS_ST_SR_END_OF_EARLY_DATA:
        return "TLSv1.3 read end of early data";
    default:
        return "unknown state";
    }
}