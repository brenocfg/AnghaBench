#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  anyPolicy; } ;
typedef  TYPE_1__ X509_POLICY_CACHE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  policy_data_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_POLICY_DATA_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 

void policy_cache_free(X509_POLICY_CACHE *cache)
{
    if (!cache)
        return;
    policy_data_free(cache->anyPolicy);
    sk_X509_POLICY_DATA_pop_free(cache->data, policy_data_free);
    OPENSSL_free(cache);
}