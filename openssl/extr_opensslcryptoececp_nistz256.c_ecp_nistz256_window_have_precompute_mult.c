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
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/ * EC_GROUP_get0_generator (int /*<<< orphan*/  const*) ; 
 int HAVEPRECOMP (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ecp_nistz256_is_affine_G (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nistz256 ; 

__attribute__((used)) static int ecp_nistz256_window_have_precompute_mult(const EC_GROUP *group)
{
    /* There is a hard-coded table for the default generator. */
    const EC_POINT *generator = EC_GROUP_get0_generator(group);

    if (generator != NULL && ecp_nistz256_is_affine_G(generator)) {
        /* There is a hard-coded table for the default generator. */
        return 1;
    }

    return HAVEPRECOMP(group, nistz256);
}