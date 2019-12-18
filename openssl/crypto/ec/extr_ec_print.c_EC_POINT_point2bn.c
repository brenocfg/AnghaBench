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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 size_t EC_POINT_point2buf (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 

BIGNUM *EC_POINT_point2bn(const EC_GROUP *group,
                          const EC_POINT *point,
                          point_conversion_form_t form,
                          BIGNUM *ret, BN_CTX *ctx)
{
    size_t buf_len = 0;
    unsigned char *buf;

    buf_len = EC_POINT_point2buf(group, point, form, &buf, ctx);

    if (buf_len == 0)
        return NULL;

    ret = BN_bin2bn(buf, buf_len, ret);

    OPENSSL_free(buf);

    return ret;
}