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
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2binpad (int /*<<< orphan*/  const*,unsigned char*,size_t) ; 
 size_t BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_F_EC_POINT_BN2POINT ; 
 int /*<<< orphan*/  EC_POINT_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_oct2point (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 

EC_POINT *EC_POINT_bn2point(const EC_GROUP *group,
                            const BIGNUM *bn, EC_POINT *point, BN_CTX *ctx)
{
    size_t buf_len = 0;
    unsigned char *buf;
    EC_POINT *ret;

    if ((buf_len = BN_num_bytes(bn)) == 0)
        buf_len = 1;
    if ((buf = OPENSSL_malloc(buf_len)) == NULL) {
        ECerr(EC_F_EC_POINT_BN2POINT, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (!BN_bn2binpad(bn, buf, buf_len)) {
        OPENSSL_free(buf);
        return NULL;
    }

    if (point == NULL) {
        if ((ret = EC_POINT_new(group)) == NULL) {
            OPENSSL_free(buf);
            return NULL;
        }
    } else
        ret = point;

    if (!EC_POINT_oct2point(group, ret, buf, buf_len, ctx)) {
        if (ret != point)
            EC_POINT_clear_free(ret);
        OPENSSL_free(buf);
        return NULL;
    }

    OPENSSL_free(buf);
    return ret;
}