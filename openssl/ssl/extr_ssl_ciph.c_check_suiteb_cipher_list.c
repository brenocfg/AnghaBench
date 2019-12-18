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
struct TYPE_8__ {int cert_flags; } ;
struct TYPE_7__ {TYPE_1__* ssl3_enc; } ;
struct TYPE_6__ {int enc_flags; } ;
typedef  TYPE_2__ SSL_METHOD ;
typedef  TYPE_3__ CERT ;

/* Variables and functions */
#define  SSL_CERT_FLAG_SUITEB_128_LOS 130 
#define  SSL_CERT_FLAG_SUITEB_128_LOS_ONLY 129 
#define  SSL_CERT_FLAG_SUITEB_192_LOS 128 
 int SSL_ENC_FLAG_TLS1_2_CIPHERS ; 
 int /*<<< orphan*/  SSL_F_CHECK_SUITEB_CIPHER_LIST ; 
 int /*<<< orphan*/  SSL_R_AT_LEAST_TLS_1_2_NEEDED_IN_SUITEB_MODE ; 
 int /*<<< orphan*/  SSL_R_ECDH_REQUIRED_FOR_SUITEB_MODE ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int check_suiteb_cipher_list(const SSL_METHOD *meth, CERT *c,
                                    const char **prule_str)
{
    unsigned int suiteb_flags = 0, suiteb_comb2 = 0;
    if (strncmp(*prule_str, "SUITEB128ONLY", 13) == 0) {
        suiteb_flags = SSL_CERT_FLAG_SUITEB_128_LOS_ONLY;
    } else if (strncmp(*prule_str, "SUITEB128C2", 11) == 0) {
        suiteb_comb2 = 1;
        suiteb_flags = SSL_CERT_FLAG_SUITEB_128_LOS;
    } else if (strncmp(*prule_str, "SUITEB128", 9) == 0) {
        suiteb_flags = SSL_CERT_FLAG_SUITEB_128_LOS;
    } else if (strncmp(*prule_str, "SUITEB192", 9) == 0) {
        suiteb_flags = SSL_CERT_FLAG_SUITEB_192_LOS;
    }

    if (suiteb_flags) {
        c->cert_flags &= ~SSL_CERT_FLAG_SUITEB_128_LOS;
        c->cert_flags |= suiteb_flags;
    } else {
        suiteb_flags = c->cert_flags & SSL_CERT_FLAG_SUITEB_128_LOS;
    }

    if (!suiteb_flags)
        return 1;
    /* Check version: if TLS 1.2 ciphers allowed we can use Suite B */

    if (!(meth->ssl3_enc->enc_flags & SSL_ENC_FLAG_TLS1_2_CIPHERS)) {
        SSLerr(SSL_F_CHECK_SUITEB_CIPHER_LIST,
               SSL_R_AT_LEAST_TLS_1_2_NEEDED_IN_SUITEB_MODE);
        return 0;
    }
# ifndef OPENSSL_NO_EC
    switch (suiteb_flags) {
    case SSL_CERT_FLAG_SUITEB_128_LOS:
        if (suiteb_comb2)
            *prule_str = "ECDHE-ECDSA-AES256-GCM-SHA384";
        else
            *prule_str =
                "ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384";
        break;
    case SSL_CERT_FLAG_SUITEB_128_LOS_ONLY:
        *prule_str = "ECDHE-ECDSA-AES128-GCM-SHA256";
        break;
    case SSL_CERT_FLAG_SUITEB_192_LOS:
        *prule_str = "ECDHE-ECDSA-AES256-GCM-SHA384";
        break;
    }
    return 1;
# else
    SSLerr(SSL_F_CHECK_SUITEB_CIPHER_LIST, SSL_R_ECDH_REQUIRED_FOR_SUITEB_MODE);
    return 0;
# endif
}