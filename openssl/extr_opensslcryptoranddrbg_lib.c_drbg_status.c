#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 scalar_t__ DRBG_READY ; 
 TYPE_1__* RAND_DRBG_get0_master () ; 
 int /*<<< orphan*/  rand_drbg_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  rand_drbg_unlock (TYPE_1__*) ; 

__attribute__((used)) static int drbg_status(void)
{
    int ret;
    RAND_DRBG *drbg = RAND_DRBG_get0_master();

    if (drbg == NULL)
        return 0;

    rand_drbg_lock(drbg);
    ret = drbg->state == DRBG_READY ? 1 : 0;
    rand_drbg_unlock(drbg);
    return ret;
}