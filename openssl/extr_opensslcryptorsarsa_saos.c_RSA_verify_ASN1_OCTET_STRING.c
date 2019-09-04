#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,unsigned int) ; 
 unsigned char* OPENSSL_malloc (unsigned int) ; 
 int /*<<< orphan*/  RSA_F_RSA_VERIFY_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 int /*<<< orphan*/  RSA_R_BAD_SIGNATURE ; 
 int /*<<< orphan*/  RSA_R_WRONG_SIGNATURE_LENGTH ; 
 int RSA_public_decrypt (int,unsigned char*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RSA_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* d2i_ASN1_OCTET_STRING (int /*<<< orphan*/ *,unsigned char const**,long) ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,unsigned int) ; 

int RSA_verify_ASN1_OCTET_STRING(int dtype,
                                 const unsigned char *m,
                                 unsigned int m_len, unsigned char *sigbuf,
                                 unsigned int siglen, RSA *rsa)
{
    int i, ret = 0;
    unsigned char *s;
    const unsigned char *p;
    ASN1_OCTET_STRING *sig = NULL;

    if (siglen != (unsigned int)RSA_size(rsa)) {
        RSAerr(RSA_F_RSA_VERIFY_ASN1_OCTET_STRING,
               RSA_R_WRONG_SIGNATURE_LENGTH);
        return 0;
    }

    s = OPENSSL_malloc((unsigned int)siglen);
    if (s == NULL) {
        RSAerr(RSA_F_RSA_VERIFY_ASN1_OCTET_STRING, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    i = RSA_public_decrypt((int)siglen, sigbuf, s, rsa, RSA_PKCS1_PADDING);

    if (i <= 0)
        goto err;

    p = s;
    sig = d2i_ASN1_OCTET_STRING(NULL, &p, (long)i);
    if (sig == NULL)
        goto err;

    if (((unsigned int)sig->length != m_len) ||
        (memcmp(m, sig->data, m_len) != 0)) {
        RSAerr(RSA_F_RSA_VERIFY_ASN1_OCTET_STRING, RSA_R_BAD_SIGNATURE);
    } else {
        ret = 1;
    }
 err:
    ASN1_OCTET_STRING_free(sig);
    OPENSSL_clear_free(s, (unsigned int)siglen);
    return ret;
}