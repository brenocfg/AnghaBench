#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* dh; } ;
struct TYPE_8__ {TYPE_1__ pkey; int /*<<< orphan*/ * ameth; } ;
struct TYPE_7__ {int /*<<< orphan*/  q; int /*<<< orphan*/  g; int /*<<< orphan*/  p; } ;
typedef  TYPE_3__ EVP_PKEY ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dhx_asn1_meth ; 

__attribute__((used)) static int dh_cmp_parameters(const EVP_PKEY *a, const EVP_PKEY *b)
{
    if (BN_cmp(a->pkey.dh->p, b->pkey.dh->p) ||
        BN_cmp(a->pkey.dh->g, b->pkey.dh->g))
        return 0;
    else if (a->ameth == &dhx_asn1_meth) {
        if (BN_cmp(a->pkey.dh->q, b->pkey.dh->q))
            return 0;
    }
    return 1;
}