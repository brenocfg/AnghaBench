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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;

/* Variables and functions */
 int CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 

int ossl_property_write_lock(OSSL_METHOD_STORE *p)
{
    return p != NULL ? CRYPTO_THREAD_write_lock(p->lock) : 0;
}