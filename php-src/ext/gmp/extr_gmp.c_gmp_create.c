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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  mpz_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmp_ce ; 
 int /*<<< orphan*/  gmp_create_object_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gmp_create(zval *target, mpz_ptr *gmpnum_target) /* {{{ */
{
	ZVAL_OBJ(target, gmp_create_object_ex(gmp_ce, gmpnum_target));
}