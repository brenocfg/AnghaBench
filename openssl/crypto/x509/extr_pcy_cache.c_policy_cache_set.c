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
typedef  int /*<<< orphan*/  X509_POLICY_CACHE ;
struct TYPE_4__ {int /*<<< orphan*/  const* policy_cache; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_cache_new (TYPE_1__*) ; 

const X509_POLICY_CACHE *policy_cache_set(X509 *x)
{

    if (x->policy_cache == NULL) {
        CRYPTO_THREAD_write_lock(x->lock);
        policy_cache_new(x);
        CRYPTO_THREAD_unlock(x->lock);
    }

    return x->policy_cache;

}