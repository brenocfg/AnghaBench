#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  handshake_buffer; } ;
struct TYPE_8__ {scalar_t__ hand_state; } ;
struct TYPE_10__ {size_t cert_verify_hash_len; TYPE_2__ s3; int /*<<< orphan*/  cert_verify_hash; TYPE_1__ statem; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 long BIO_get_mem_data (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_GET_CERT_VERIFY_TBS_DATA ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TLS13_TBS_PREAMBLE_SIZE ; 
 int TLS13_TBS_START_SIZE ; 
 scalar_t__ TLS_ST_CR_CERT_VRFY ; 
 scalar_t__ TLS_ST_SR_CERT_VRFY ; 
 scalar_t__ TLS_ST_SW_CERT_VRFY ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  ssl_handshake_hash (TYPE_3__*,unsigned char*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static int get_cert_verify_tbs_data(SSL *s, unsigned char *tls13tbs,
                                    void **hdata, size_t *hdatalen)
{
#ifdef CHARSET_EBCDIC
    static const char servercontext[] = { 0x54, 0x4c, 0x53, 0x20, 0x31, 0x2e,
     0x33, 0x2c, 0x20, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x20, 0x43, 0x65,
     0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x56, 0x65, 0x72,
     0x69, 0x66, 0x79, 0x00 };
    static const char clientcontext[] = { 0x54, 0x4c, 0x53, 0x20, 0x31, 0x2e,
     0x33, 0x2c, 0x20, 0x63, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x20, 0x43, 0x65,
     0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x56, 0x65, 0x72,
     0x69, 0x66, 0x79, 0x00 };
#else
    static const char servercontext[] = "TLS 1.3, server CertificateVerify";
    static const char clientcontext[] = "TLS 1.3, client CertificateVerify";
#endif
    if (SSL_IS_TLS13(s)) {
        size_t hashlen;

        /* Set the first 64 bytes of to-be-signed data to octet 32 */
        memset(tls13tbs, 32, TLS13_TBS_START_SIZE);
        /* This copies the 33 bytes of context plus the 0 separator byte */
        if (s->statem.hand_state == TLS_ST_CR_CERT_VRFY
                 || s->statem.hand_state == TLS_ST_SW_CERT_VRFY)
            strcpy((char *)tls13tbs + TLS13_TBS_START_SIZE, servercontext);
        else
            strcpy((char *)tls13tbs + TLS13_TBS_START_SIZE, clientcontext);

        /*
         * If we're currently reading then we need to use the saved handshake
         * hash value. We can't use the current handshake hash state because
         * that includes the CertVerify itself.
         */
        if (s->statem.hand_state == TLS_ST_CR_CERT_VRFY
                || s->statem.hand_state == TLS_ST_SR_CERT_VRFY) {
            memcpy(tls13tbs + TLS13_TBS_PREAMBLE_SIZE, s->cert_verify_hash,
                   s->cert_verify_hash_len);
            hashlen = s->cert_verify_hash_len;
        } else if (!ssl_handshake_hash(s, tls13tbs + TLS13_TBS_PREAMBLE_SIZE,
                                       EVP_MAX_MD_SIZE, &hashlen)) {
            /* SSLfatal() already called */
            return 0;
        }

        *hdata = tls13tbs;
        *hdatalen = TLS13_TBS_PREAMBLE_SIZE + hashlen;
    } else {
        size_t retlen;
        long retlen_l;

        retlen = retlen_l = BIO_get_mem_data(s->s3.handshake_buffer, hdata);
        if (retlen_l <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_GET_CERT_VERIFY_TBS_DATA,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
        *hdatalen = retlen;
    }

    return 1;
}