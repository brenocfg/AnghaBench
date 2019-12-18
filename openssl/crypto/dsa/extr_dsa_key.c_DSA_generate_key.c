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
struct TYPE_6__ {int (* dsa_keygen ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ DSA ;

/* Variables and functions */
 int dsa_builtin_keygen (TYPE_2__*) ; 
 int stub1 (TYPE_2__*) ; 

int DSA_generate_key(DSA *dsa)
{
    if (dsa->meth->dsa_keygen)
        return dsa->meth->dsa_keygen(dsa);
    return dsa_builtin_keygen(dsa);
}