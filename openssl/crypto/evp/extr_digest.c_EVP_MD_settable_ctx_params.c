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
struct TYPE_3__ {int /*<<< orphan*/  const* (* settable_ctx_params ) () ;} ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  const* stub1 () ; 

const OSSL_PARAM *EVP_MD_settable_ctx_params(const EVP_MD *md)
{
    if (md != NULL && md->settable_ctx_params != NULL)
        return md->settable_ctx_params();
    return NULL;
}