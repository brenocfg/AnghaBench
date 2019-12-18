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
typedef  int /*<<< orphan*/  X509_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int i2d_X509_NAME (int /*<<< orphan*/ *,unsigned char**) ; 
 int memcmp (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int xname_cmp(const X509_NAME *a, const X509_NAME *b)
{
    unsigned char *abuf = NULL, *bbuf = NULL;
    int alen, blen, ret;

    /* X509_NAME_cmp() itself casts away constness in this way, so
     * assume it's safe:
     */
    alen = i2d_X509_NAME((X509_NAME *)a, &abuf);
    blen = i2d_X509_NAME((X509_NAME *)b, &bbuf);

    if (alen < 0 || blen < 0)
        ret = -2;
    else if (alen != blen)
        ret = alen - blen;
    else /* alen == blen */
        ret = memcmp(abuf, bbuf, alen);

    OPENSSL_free(abuf);
    OPENSSL_free(bbuf);

    return ret;
}