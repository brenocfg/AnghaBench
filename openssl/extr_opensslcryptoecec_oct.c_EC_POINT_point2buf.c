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
typedef  int /*<<< orphan*/  point_conversion_form_t ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_EC_POINT_POINT2BUF ; 
 size_t EC_POINT_point2oct (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 

size_t EC_POINT_point2buf(const EC_GROUP *group, const EC_POINT *point,
                          point_conversion_form_t form,
                          unsigned char **pbuf, BN_CTX *ctx)
{
    size_t len;
    unsigned char *buf;

    len = EC_POINT_point2oct(group, point, form, NULL, 0, NULL);
    if (len == 0)
        return 0;
    if ((buf = OPENSSL_malloc(len)) == NULL) {
        ECerr(EC_F_EC_POINT_POINT2BUF, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    len = EC_POINT_point2oct(group, point, form, buf, len, ctx);
    if (len == 0) {
        OPENSSL_free(buf);
        return 0;
    }
    *pbuf = buf;
    return len;
}