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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mod; int /*<<< orphan*/  e; int /*<<< orphan*/  Ai; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ BN_BLINDING ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void BN_BLINDING_free(BN_BLINDING *r)
{
    if (r == NULL)
        return;
    BN_free(r->A);
    BN_free(r->Ai);
    BN_free(r->e);
    BN_free(r->mod);
    CRYPTO_THREAD_lock_free(r->lock);
    OPENSSL_free(r);
}