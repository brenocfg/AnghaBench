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
 int /*<<< orphan*/  CRYPTO_F_OPENSSL_BUF2HEXSTR ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ OPENSSL_buf2hexstr_ex (char*,size_t,int /*<<< orphan*/ *,unsigned char const*,long) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (size_t) ; 
 char* OPENSSL_zalloc (int) ; 

char *OPENSSL_buf2hexstr(const unsigned char *buf, long buflen)
{
    char *tmp;
    size_t tmp_n;

    if (buflen == 0)
        return OPENSSL_zalloc(1);

    tmp_n = buflen * 3;
    if ((tmp = OPENSSL_malloc(tmp_n)) == NULL) {
        CRYPTOerr(CRYPTO_F_OPENSSL_BUF2HEXSTR, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (OPENSSL_buf2hexstr_ex(tmp, tmp_n, NULL, buf, buflen))
        return tmp;
    OPENSSL_free(tmp);
    return NULL;
}