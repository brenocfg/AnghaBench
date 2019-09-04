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
typedef  int /*<<< orphan*/  felem ;

/* Variables and functions */
 int /*<<< orphan*/  ec_GFp_nistp_points_make_affine_internal (size_t,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,void (*) (void*),int /*<<< orphan*/ ,void (*) (void*,void const*),void (*) (void*,void const*),void (*) (void*,void const*,void const*),void (*) (void*,void const*),void (*) (void*,void const*)) ; 
 scalar_t__ felem_assign ; 
 scalar_t__ felem_contract ; 
 scalar_t__ felem_inv ; 
 int /*<<< orphan*/  felem_is_zero_int ; 
 scalar_t__ felem_mul_reduce ; 
 scalar_t__ felem_one ; 
 scalar_t__ felem_square_reduce ; 

__attribute__((used)) static void make_points_affine(size_t num, felem points[ /* num */ ][3],
                               felem tmp_felems[ /* num+1 */ ])
{
    /*
     * Runs in constant time, unless an input is the point at infinity (which
     * normally shouldn't happen).
     */
    ec_GFp_nistp_points_make_affine_internal(num,
                                             points,
                                             sizeof(felem),
                                             tmp_felems,
                                             (void (*)(void *))felem_one,
                                             felem_is_zero_int,
                                             (void (*)(void *, const void *))
                                             felem_assign,
                                             (void (*)(void *, const void *))
                                             felem_square_reduce, (void (*)
                                                                   (void *,
                                                                    const void
                                                                    *,
                                                                    const void
                                                                    *))
                                             felem_mul_reduce,
                                             (void (*)(void *, const void *))
                                             felem_inv,
                                             (void (*)(void *, const void *))
                                             felem_contract);
}