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
struct TYPE_3__ {int /*<<< orphan*/  provctx; int /*<<< orphan*/  const* (* query_operation ) (int /*<<< orphan*/ ,int,int*) ;} ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  const* stub1 (int /*<<< orphan*/ ,int,int*) ; 

const OSSL_ALGORITHM *ossl_provider_query_operation(const OSSL_PROVIDER *prov,
                                                    int operation_id,
                                                    int *no_cache)
{
    return prov->query_operation(prov->provctx, operation_id, no_cache);
}