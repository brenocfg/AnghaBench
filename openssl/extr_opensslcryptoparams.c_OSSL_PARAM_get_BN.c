#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ data_type; scalar_t__ data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_native2bn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ OSSL_PARAM_UNSIGNED_INTEGER ; 

int OSSL_PARAM_get_BN(const OSSL_PARAM *p, BIGNUM **val)
{
    BIGNUM *b;

    if (val == NULL
        || p == NULL
        || p->data_type != OSSL_PARAM_UNSIGNED_INTEGER)
        return 0;

    b = BN_native2bn(p->data, (int)p->data_size, *val);
    if (b != NULL) {
        *val = b;
        return 1;
    }
    return 0;
}