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
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BN_GENCB ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GENCB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_GENCB_new () ; 
 int /*<<< orphan*/  BN_GENCB_set_old (int /*<<< orphan*/ *,void (*) (int,int,void*),void*) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 scalar_t__ DH_generate_parameters_ex (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_new () ; 

DH *DH_generate_parameters(int prime_len, int generator,
                           void (*callback) (int, int, void *), void *cb_arg)
{
    BN_GENCB *cb;
    DH *ret = NULL;

    if ((ret = DH_new()) == NULL)
        return NULL;
    cb = BN_GENCB_new();
    if (cb == NULL) {
        DH_free(ret);
        return NULL;
    }

    BN_GENCB_set_old(cb, callback, cb_arg);

    if (DH_generate_parameters_ex(ret, prime_len, generator, cb)) {
        BN_GENCB_free(cb);
        return ret;
    }
    BN_GENCB_free(cb);
    DH_free(ret);
    return NULL;
}