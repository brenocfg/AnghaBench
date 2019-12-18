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
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/ * EC_POINT_bn2point (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

EC_POINT *EC_POINT_hex2point(const EC_GROUP *group,
                             const char *buf, EC_POINT *point, BN_CTX *ctx)
{
    EC_POINT *ret = NULL;
    BIGNUM *tmp_bn = NULL;

    if (!BN_hex2bn(&tmp_bn, buf))
        return NULL;

    ret = EC_POINT_bn2point(group, tmp_bn, point, ctx);

    BN_clear_free(tmp_bn);

    return ret;
}