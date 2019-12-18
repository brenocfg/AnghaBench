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
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_EC_KEY_PRIV2BUF ; 
 size_t EC_KEY_priv2oct (int /*<<< orphan*/  const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 

size_t EC_KEY_priv2buf(const EC_KEY *eckey, unsigned char **pbuf)
{
    size_t len;
    unsigned char *buf;

    len = EC_KEY_priv2oct(eckey, NULL, 0);
    if (len == 0)
        return 0;
    if ((buf = OPENSSL_malloc(len)) == NULL) {
        ECerr(EC_F_EC_KEY_PRIV2BUF, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    len = EC_KEY_priv2oct(eckey, buf, len);
    if (len == 0) {
        OPENSSL_free(buf);
        return 0;
    }
    *pbuf = buf;
    return len;
}