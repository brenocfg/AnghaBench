#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* dh; } ;
struct TYPE_10__ {TYPE_2__ pkey; } ;
struct TYPE_8__ {int /*<<< orphan*/  pub_key; } ;
typedef  TYPE_3__ EVP_PKEY ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dh_cmp_parameters (TYPE_3__ const*,TYPE_3__ const*) ; 

__attribute__((used)) static int dh_pub_cmp(const EVP_PKEY *a, const EVP_PKEY *b)
{
    if (dh_cmp_parameters(a, b) == 0)
        return 0;
    if (BN_cmp(b->pkey.dh->pub_key, a->pkey.dh->pub_key) != 0)
        return 0;
    else
        return 1;
}