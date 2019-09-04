#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  nid; } ;
struct TYPE_6__ {int /*<<< orphan*/  algs; } ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;
typedef  TYPE_2__ ALGORITHM ;

/* Variables and functions */
 int ossl_sa_ALGORITHM_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int ossl_method_store_insert(OSSL_METHOD_STORE *store, ALGORITHM *alg)
{
        return ossl_sa_ALGORITHM_set(store->algs, alg->nid, alg);
}