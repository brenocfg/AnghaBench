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
struct TYPE_6__ {unsigned char* ciphers_raw; scalar_t__ ciphers_rawlen; } ;
struct TYPE_7__ {TYPE_1__ tmp; } ;
struct TYPE_8__ {TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  PACKET_copy_bytes (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_memdup (int /*<<< orphan*/ *,unsigned char**,scalar_t__*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 size_t SSLV2_CIPHER_LEN ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL_CACHE_CIPHERLIST ; 
 int /*<<< orphan*/  SSL_R_BAD_PACKET ; 
 int /*<<< orphan*/  SSL_R_ERROR_IN_RECEIVED_CIPHER_LIST ; 
 int /*<<< orphan*/  SSL_R_NO_CIPHERS_SPECIFIED ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TLS_CIPHER_LEN ; 

int ssl_cache_cipherlist(SSL *s, PACKET *cipher_suites, int sslv2format)
{
    int n;

    n = sslv2format ? SSLV2_CIPHER_LEN : TLS_CIPHER_LEN;

    if (PACKET_remaining(cipher_suites) == 0) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_SSL_CACHE_CIPHERLIST,
                 SSL_R_NO_CIPHERS_SPECIFIED);
        return 0;
    }

    if (PACKET_remaining(cipher_suites) % n != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_SSL_CACHE_CIPHERLIST,
                 SSL_R_ERROR_IN_RECEIVED_CIPHER_LIST);
        return 0;
    }

    OPENSSL_free(s->s3.tmp.ciphers_raw);
    s->s3.tmp.ciphers_raw = NULL;
    s->s3.tmp.ciphers_rawlen = 0;

    if (sslv2format) {
        size_t numciphers = PACKET_remaining(cipher_suites) / n;
        PACKET sslv2ciphers = *cipher_suites;
        unsigned int leadbyte;
        unsigned char *raw;

        /*
         * We store the raw ciphers list in SSLv3+ format so we need to do some
         * preprocessing to convert the list first. If there are any SSLv2 only
         * ciphersuites with a non-zero leading byte then we are going to
         * slightly over allocate because we won't store those. But that isn't a
         * problem.
         */
        raw = OPENSSL_malloc(numciphers * TLS_CIPHER_LEN);
        s->s3.tmp.ciphers_raw = raw;
        if (raw == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_CACHE_CIPHERLIST,
                     ERR_R_MALLOC_FAILURE);
            return 0;
        }
        for (s->s3.tmp.ciphers_rawlen = 0;
             PACKET_remaining(&sslv2ciphers) > 0;
             raw += TLS_CIPHER_LEN) {
            if (!PACKET_get_1(&sslv2ciphers, &leadbyte)
                    || (leadbyte == 0
                        && !PACKET_copy_bytes(&sslv2ciphers, raw,
                                              TLS_CIPHER_LEN))
                    || (leadbyte != 0
                        && !PACKET_forward(&sslv2ciphers, TLS_CIPHER_LEN))) {
                SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_SSL_CACHE_CIPHERLIST,
                         SSL_R_BAD_PACKET);
                OPENSSL_free(s->s3.tmp.ciphers_raw);
                s->s3.tmp.ciphers_raw = NULL;
                s->s3.tmp.ciphers_rawlen = 0;
                return 0;
            }
            if (leadbyte == 0)
                s->s3.tmp.ciphers_rawlen += TLS_CIPHER_LEN;
        }
    } else if (!PACKET_memdup(cipher_suites, &s->s3.tmp.ciphers_raw,
                           &s->s3.tmp.ciphers_rawlen)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_CACHE_CIPHERLIST,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
    return 1;
}