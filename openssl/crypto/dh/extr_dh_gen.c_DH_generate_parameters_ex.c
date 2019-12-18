#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* meth; } ;
struct TYPE_6__ {int (* generate_params ) (TYPE_2__*,int,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ DH ;
typedef  int /*<<< orphan*/  BN_GENCB ;

/* Variables and functions */
 int dh_builtin_genparams (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 

int DH_generate_parameters_ex(DH *ret, int prime_len, int generator,
                              BN_GENCB *cb)
{
    if (ret->meth->generate_params)
        return ret->meth->generate_params(ret, prime_len, generator, cb);
    return dh_builtin_genparams(ret, prime_len, generator, cb);
}