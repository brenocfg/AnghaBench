#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  priv_key; int /*<<< orphan*/  pub_key; int /*<<< orphan*/  group; } ;
typedef  TYPE_1__ EC_KEY ;

/* Variables and functions */
 int EC_POINT_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ec_key_simple_generate_public_key(EC_KEY *eckey)
{
    /*
     * See SP800-56AR3 5.6.1.2.2: Step (8)
     * pub_key = priv_key * G (where G is a point on the curve)
     */
    return EC_POINT_mul(eckey->group, eckey->pub_key, eckey->priv_key, NULL,
                        NULL, NULL);
}