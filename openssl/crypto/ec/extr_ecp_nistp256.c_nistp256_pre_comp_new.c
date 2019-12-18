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
struct TYPE_5__ {int references; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ NISTP256_PRE_COMP ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  EC_F_NISTP256_PRE_COMP_NEW ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static NISTP256_PRE_COMP *nistp256_pre_comp_new(void)
{
    NISTP256_PRE_COMP *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        ECerr(EC_F_NISTP256_PRE_COMP_NEW, ERR_R_MALLOC_FAILURE);
        return ret;
    }

    ret->references = 1;

    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        ECerr(EC_F_NISTP256_PRE_COMP_NEW, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }
    return ret;
}