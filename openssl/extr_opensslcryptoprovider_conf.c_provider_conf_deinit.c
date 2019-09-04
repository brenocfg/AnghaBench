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
typedef  int /*<<< orphan*/  CONF_IMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  CONF ; 
 int /*<<< orphan*/  OSSL_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * activated_providers ; 
 int /*<<< orphan*/  ossl_provider_free ; 
 int /*<<< orphan*/  sk_OSSL_PROVIDER_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void provider_conf_deinit(CONF_IMODULE *md)
{
    sk_OSSL_PROVIDER_pop_free(activated_providers, ossl_provider_free);
    activated_providers = NULL;
    OSSL_TRACE(CONF, "Cleaned up providers\n");
}