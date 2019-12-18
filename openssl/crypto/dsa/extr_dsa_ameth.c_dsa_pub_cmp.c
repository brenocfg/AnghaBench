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
struct TYPE_7__ {TYPE_1__* dsa; } ;
struct TYPE_8__ {TYPE_2__ pkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  pub_key; } ;
typedef  TYPE_3__ EVP_PKEY ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_pub_cmp(const EVP_PKEY *a, const EVP_PKEY *b)
{
    if (BN_cmp(b->pkey.dsa->pub_key, a->pkey.dsa->pub_key) != 0)
        return 0;
    else
        return 1;
}