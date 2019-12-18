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

/* Variables and functions */
 int /*<<< orphan*/  ossl_provider_free (int /*<<< orphan*/ *) ; 

int OSSL_PROVIDER_unload(OSSL_PROVIDER *prov)
{
    ossl_provider_free(prov);
    return 1;
}