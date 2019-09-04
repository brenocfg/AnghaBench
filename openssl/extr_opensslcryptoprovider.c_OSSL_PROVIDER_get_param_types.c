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
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  const* ossl_provider_get_param_types (int /*<<< orphan*/ *) ; 

const OSSL_ITEM *OSSL_PROVIDER_get_param_types(OSSL_PROVIDER *prov)
{
    return ossl_provider_get_param_types(prov);
}