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
typedef  int /*<<< orphan*/  NETSCAPE_SPKI ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_DecodeBlock (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  X509_F_NETSCAPE_SPKI_B64_DECODE ; 
 int /*<<< orphan*/  X509_R_BASE64_DECODE_ERROR ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_NETSCAPE_SPKI (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 int strlen (char const*) ; 

NETSCAPE_SPKI *NETSCAPE_SPKI_b64_decode(const char *str, int len)
{
    unsigned char *spki_der;
    const unsigned char *p;
    int spki_len;
    NETSCAPE_SPKI *spki;
    if (len <= 0)
        len = strlen(str);
    if ((spki_der = OPENSSL_malloc(len + 1)) == NULL) {
        X509err(X509_F_NETSCAPE_SPKI_B64_DECODE, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    spki_len = EVP_DecodeBlock(spki_der, (const unsigned char *)str, len);
    if (spki_len < 0) {
        X509err(X509_F_NETSCAPE_SPKI_B64_DECODE, X509_R_BASE64_DECODE_ERROR);
        OPENSSL_free(spki_der);
        return NULL;
    }
    p = spki_der;
    spki = d2i_NETSCAPE_SPKI(NULL, &p, spki_len);
    OPENSSL_free(spki_der);
    return spki;
}