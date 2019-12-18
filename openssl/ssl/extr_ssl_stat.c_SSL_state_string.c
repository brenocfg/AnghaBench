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

const char *SSL_state_string(const SSL *s)
{
    if (ossl_statem_in_error(s))
        return "SSLERR";

    switch (SSL_get_state(s)) {
    case TLS_ST_SR_NEXT_PROTO:
        return "TRNP";
    case TLS_ST_SW_SESSION_TICKET:
        return "TWST";
    case TLS_ST_SW_CERT_STATUS:
        return "TWCS";
    case TLS_ST_CR_CERT_STATUS:
        return "TRCS";
    case TLS_ST_CR_SESSION_TICKET:
        return "TRST";
    case TLS_ST_CW_NEXT_PROTO:
        return "TWNP";
    case TLS_ST_BEFORE:
        return "PINIT ";
    case TLS_ST_OK:
        return "SSLOK ";
    case TLS_ST_CW_CLNT_HELLO:
        return "TWCH";
    case TLS_ST_CR_SRVR_HELLO:
        return "TRSH";
    case TLS_ST_CR_CERT:
        return "TRSC";
    case TLS_ST_CR_KEY_EXCH:
        return "TRSKE";
    case TLS_ST_CR_CERT_REQ:
        return "TRCR";
    case TLS_ST_CR_SRVR_DONE:
        return "TRSD";
    case TLS_ST_CW_CERT:
        return "TWCC";
    case TLS_ST_CW_KEY_EXCH:
        return "TWCKE";
    case TLS_ST_CW_CERT_VRFY:
        return "TWCV";
    case TLS_ST_SW_CHANGE:
    case TLS_ST_CW_CHANGE:
        return "TWCCS";
    case TLS_ST_SW_FINISHED:
    case TLS_ST_CW_FINISHED:
        return "TWFIN";
    case TLS_ST_SR_CHANGE:
    case TLS_ST_CR_CHANGE:
        return "TRCCS";
    case TLS_ST_SR_FINISHED:
    case TLS_ST_CR_FINISHED:
        return "TRFIN";
    case TLS_ST_SW_HELLO_REQ:
        return "TWHR";
    case TLS_ST_SR_CLNT_HELLO:
        return "TRCH";
    case TLS_ST_SW_SRVR_HELLO:
        return "TWSH";
    case TLS_ST_SW_CERT:
        return "TWSC";
    case TLS_ST_SW_KEY_EXCH:
        return "TWSKE";
    case TLS_ST_SW_CERT_REQ:
        return "TWCR";
    case TLS_ST_SW_SRVR_DONE:
        return "TWSD";
    case TLS_ST_SR_CERT:
        return "TRCC";
    case TLS_ST_SR_KEY_EXCH:
        return "TRCKE";
    case TLS_ST_SR_CERT_VRFY:
        return "TRCV";
    case DTLS_ST_CR_HELLO_VERIFY_REQUEST:
        return "DRCHV";
    case DTLS_ST_SW_HELLO_VERIFY_REQUEST:
        return "DWCHV";
    case TLS_ST_SW_ENCRYPTED_EXTENSIONS:
        return "TWEE";
    case TLS_ST_CR_ENCRYPTED_EXTENSIONS:
        return "TREE";
    case TLS_ST_CR_CERT_VRFY:
        return "TRSCV";
    case TLS_ST_SW_CERT_VRFY:
        return "TRSCV";
    case TLS_ST_CR_HELLO_REQ:
        return "TRHR";
    case TLS_ST_SW_KEY_UPDATE:
        return "TWSKU";
    case TLS_ST_CW_KEY_UPDATE:
        return "TWCKU";
    case TLS_ST_SR_KEY_UPDATE:
        return "TRCKU";
    case TLS_ST_CR_KEY_UPDATE:
        return "TRSKU";
    case TLS_ST_EARLY_DATA:
        return "TED";
    case TLS_ST_PENDING_EARLY_DATA_END:
        return "TPEDE";
    case TLS_ST_CW_END_OF_EARLY_DATA:
        return "TWEOED";
    case TLS_ST_SR_END_OF_EARLY_DATA:
        return "TWEOED";
    default:
        return "UNKWN ";
    }
}