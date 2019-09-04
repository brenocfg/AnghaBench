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
struct TYPE_4__ {scalar_t__ data_type; size_t data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_bn2nativepad (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_num_bytes (int /*<<< orphan*/  const*) ; 
 scalar_t__ OSSL_PARAM_UNSIGNED_INTEGER ; 
 int /*<<< orphan*/  SET_RETURN_SIZE (TYPE_1__ const*,size_t) ; 

int OSSL_PARAM_set_BN(const OSSL_PARAM *p, const BIGNUM *val)
{
    size_t bytes;

    if (p == NULL)
        return 0;
    SET_RETURN_SIZE(p, 0);
    if (val == NULL || p->data_type != OSSL_PARAM_UNSIGNED_INTEGER)
        return 0;

    /* For the moment, only positive values are permitted */
    if (BN_is_negative(val))
        return 0;

    bytes = (size_t)BN_num_bytes(val);
    SET_RETURN_SIZE(p, bytes);
    return p->data_size >= bytes
        && BN_bn2nativepad(val, p->data, bytes) >= 0;
}