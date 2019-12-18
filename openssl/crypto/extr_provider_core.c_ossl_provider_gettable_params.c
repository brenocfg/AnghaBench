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
struct TYPE_3__ {int /*<<< orphan*/  provctx; int /*<<< orphan*/  const* (* gettable_params ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  const* stub1 (int /*<<< orphan*/ ) ; 

const OSSL_PARAM *ossl_provider_gettable_params(const OSSL_PROVIDER *prov)
{
    return prov->gettable_params == NULL
        ? NULL : prov->gettable_params(prov->provctx);
}