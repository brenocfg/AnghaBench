#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int algorithm_auth; int algorithm_mac; int algorithm_mkey; int /*<<< orphan*/  min_tls; int /*<<< orphan*/  algorithm_enc; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  TYPE_1__ SSL_CIPHER ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  DTLS1_2_VERSION ; 
 int /*<<< orphan*/  DTLS_VERSION_LT (int,int /*<<< orphan*/ ) ; 
 int SSL3_VERSION ; 
 int SSL_CTX_get_security_level (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_IS_DTLS (int /*<<< orphan*/  const*) ; 
 int SSL_MD5 ; 
 int /*<<< orphan*/  SSL_RC4 ; 
#define  SSL_SECOP_CIPHER_CHECK 133 
#define  SSL_SECOP_CIPHER_SHARED 132 
#define  SSL_SECOP_CIPHER_SUPPORTED 131 
#define  SSL_SECOP_COMPRESSION 130 
#define  SSL_SECOP_TICKET 129 
 int SSL_SECOP_TMP_DH ; 
#define  SSL_SECOP_VERSION 128 
 int SSL_SHA1 ; 
 int SSL_aNULL ; 
 int SSL_get_security_level (int /*<<< orphan*/  const*) ; 
 int SSL_kEDH ; 
 int SSL_kEECDH ; 
 int TLS1_1_VERSION ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int TLS1_VERSION ; 

__attribute__((used)) static int ssl_security_default_callback(const SSL *s, const SSL_CTX *ctx,
                                         int op, int bits, int nid, void *other,
                                         void *ex)
{
    int level, minbits;
    static const int minbits_table[5] = { 80, 112, 128, 192, 256 };
    if (ctx)
        level = SSL_CTX_get_security_level(ctx);
    else
        level = SSL_get_security_level(s);

    if (level <= 0) {
        /*
         * No EDH keys weaker than 1024-bits even at level 0, otherwise,
         * anything goes.
         */
        if (op == SSL_SECOP_TMP_DH && bits < 80)
            return 0;
        return 1;
    }
    if (level > 5)
        level = 5;
    minbits = minbits_table[level - 1];
    switch (op) {
    case SSL_SECOP_CIPHER_SUPPORTED:
    case SSL_SECOP_CIPHER_SHARED:
    case SSL_SECOP_CIPHER_CHECK:
        {
            const SSL_CIPHER *c = other;
            /* No ciphers below security level */
            if (bits < minbits)
                return 0;
            /* No unauthenticated ciphersuites */
            if (c->algorithm_auth & SSL_aNULL)
                return 0;
            /* No MD5 mac ciphersuites */
            if (c->algorithm_mac & SSL_MD5)
                return 0;
            /* SHA1 HMAC is 160 bits of security */
            if (minbits > 160 && c->algorithm_mac & SSL_SHA1)
                return 0;
            /* Level 2: no RC4 */
            if (level >= 2 && c->algorithm_enc == SSL_RC4)
                return 0;
            /* Level 3: forward secure ciphersuites only */
            if (level >= 3 && c->min_tls != TLS1_3_VERSION &&
                               !(c->algorithm_mkey & (SSL_kEDH | SSL_kEECDH)))
                return 0;
            break;
        }
    case SSL_SECOP_VERSION:
        if (!SSL_IS_DTLS(s)) {
            /* SSLv3 not allowed at level 2 */
            if (nid <= SSL3_VERSION && level >= 2)
                return 0;
            /* TLS v1.1 and above only for level 3 */
            if (nid <= TLS1_VERSION && level >= 3)
                return 0;
            /* TLS v1.2 only for level 4 and above */
            if (nid <= TLS1_1_VERSION && level >= 4)
                return 0;
        } else {
            /* DTLS v1.2 only for level 4 and above */
            if (DTLS_VERSION_LT(nid, DTLS1_2_VERSION) && level >= 4)
                return 0;
        }
        break;

    case SSL_SECOP_COMPRESSION:
        if (level >= 2)
            return 0;
        break;
    case SSL_SECOP_TICKET:
        if (level >= 3)
            return 0;
        break;
    default:
        if (bits < minbits)
            return 0;
    }
    return 1;
}