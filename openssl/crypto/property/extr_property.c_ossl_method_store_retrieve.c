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
struct TYPE_3__ {int /*<<< orphan*/  algs; } ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;
typedef  int /*<<< orphan*/  ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/ * ossl_sa_ALGORITHM_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ALGORITHM *ossl_method_store_retrieve(OSSL_METHOD_STORE *store, int nid)
{
    return ossl_sa_ALGORITHM_get(store->algs, nid);
}