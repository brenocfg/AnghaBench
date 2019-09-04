#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int (* pkey_ctrl ) (TYPE_2__*,int,int,void*) ;} ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int,int,void*) ; 

__attribute__((used)) static int evp_pkey_asn1_ctrl(EVP_PKEY *pkey, int op, int arg1, void *arg2)
{
    if (pkey->ameth == NULL || pkey->ameth->pkey_ctrl == NULL)
        return -2;
    return pkey->ameth->pkey_ctrl(pkey, op, arg1, arg2);
}