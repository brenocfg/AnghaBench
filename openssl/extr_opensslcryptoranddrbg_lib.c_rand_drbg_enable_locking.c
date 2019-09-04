#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/ * lock; TYPE_1__* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lock; } ;
typedef  TYPE_2__ RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 scalar_t__ DRBG_UNINITIALISED ; 
 int /*<<< orphan*/  RAND_F_RAND_DRBG_ENABLE_LOCKING ; 
 int /*<<< orphan*/  RAND_R_DRBG_ALREADY_INITIALIZED ; 
 int /*<<< orphan*/  RAND_R_FAILED_TO_CREATE_LOCK ; 
 int /*<<< orphan*/  RAND_R_PARENT_LOCKING_NOT_ENABLED ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rand_drbg_enable_locking(RAND_DRBG *drbg)
{
    if (drbg->state != DRBG_UNINITIALISED) {
        RANDerr(RAND_F_RAND_DRBG_ENABLE_LOCKING,
                RAND_R_DRBG_ALREADY_INITIALIZED);
        return 0;
    }

    if (drbg->lock == NULL) {
        if (drbg->parent != NULL && drbg->parent->lock == NULL) {
            RANDerr(RAND_F_RAND_DRBG_ENABLE_LOCKING,
                    RAND_R_PARENT_LOCKING_NOT_ENABLED);
            return 0;
        }

        drbg->lock = CRYPTO_THREAD_lock_new();
        if (drbg->lock == NULL) {
            RANDerr(RAND_F_RAND_DRBG_ENABLE_LOCKING,
                    RAND_R_FAILED_TO_CREATE_LOCK);
            return 0;
        }
    }

    return 1;
}