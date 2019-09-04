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
struct TYPE_5__ {int /*<<< orphan*/ * dh; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ameth; TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/ * DH_new () ; 
 int /*<<< orphan*/  dhx_asn1_meth ; 
 int int_dh_param_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dh_copy_parameters(EVP_PKEY *to, const EVP_PKEY *from)
{
    if (to->pkey.dh == NULL) {
        to->pkey.dh = DH_new();
        if (to->pkey.dh == NULL)
            return 0;
    }
    return int_dh_param_copy(to->pkey.dh, from->pkey.dh,
                             from->ameth == &dhx_asn1_meth);
}