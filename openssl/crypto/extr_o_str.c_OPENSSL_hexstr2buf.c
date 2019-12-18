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
 int /*<<< orphan*/  CRYPTO_F_OPENSSL_HEXSTR2BUF ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 scalar_t__ OPENSSL_hexstr2buf_ex (unsigned char*,size_t,size_t*,char const*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int strlen (char const*) ; 

unsigned char *OPENSSL_hexstr2buf(const char *str, long *buflen)
{
    unsigned char *buf;
    size_t buf_n, tmp_buflen;

    buf_n = strlen(str) >> 1;
    if ((buf = OPENSSL_malloc(buf_n)) == NULL) {
        CRYPTOerr(CRYPTO_F_OPENSSL_HEXSTR2BUF, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (buflen != NULL)
        *buflen = 0;
    tmp_buflen = 0;
    if (OPENSSL_hexstr2buf_ex(buf, buf_n, &tmp_buflen, str)) {
        if (buflen != NULL)
            *buflen = (long)tmp_buflen;
        return buf;
    }
    OPENSSL_free(buf);
    return NULL;
}