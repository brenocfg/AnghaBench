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
struct TYPE_5__ {int /*<<< orphan*/  ec; } ;
struct TYPE_6__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 scalar_t__ EC_GROUP_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ec_cmp_parameters(const EVP_PKEY *a, const EVP_PKEY *b)
{
    const EC_GROUP *group_a = EC_KEY_get0_group(a->pkey.ec),
        *group_b = EC_KEY_get0_group(b->pkey.ec);
    if (group_a == NULL || group_b == NULL)
        return -2;
    if (EC_GROUP_cmp(group_a, group_b, NULL))
        return 0;
    else
        return 1;
}