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
struct TYPE_3__ {int /*<<< orphan*/  refcnt_lock; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;

/* Variables and functions */
 scalar_t__ CRYPTO_UP_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

int ossl_provider_up_ref(OSSL_PROVIDER *prov)
{
    int ref = 0;

    if (CRYPTO_UP_REF(&prov->refcnt, &ref, prov->refcnt_lock) <= 0)
        return 0;
    return ref;
}