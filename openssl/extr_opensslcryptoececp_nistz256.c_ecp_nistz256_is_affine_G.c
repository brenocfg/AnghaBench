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
struct TYPE_3__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ EC_POINT ;

/* Variables and functions */
 scalar_t__ P256_LIMBS ; 
 scalar_t__ bn_get_top (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_get_words (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  def_xG ; 
 int /*<<< orphan*/  def_yG ; 
 scalar_t__ is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecp_nistz256_is_affine_G(const EC_POINT *generator)
{
    return (bn_get_top(generator->X) == P256_LIMBS) &&
        (bn_get_top(generator->Y) == P256_LIMBS) &&
        is_equal(bn_get_words(generator->X), def_xG) &&
        is_equal(bn_get_words(generator->Y), def_yG) &&
        is_one(generator->Z);
}