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
typedef  int /*<<< orphan*/  mpz_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_new () ; 

__attribute__((used)) static void
mp_modmul(mpz_t *a, mpz_t *b, mpz_t *p, mpz_t *res)
{
	mpz_t	   *tmp = mp_new();

	mp_int_mul(a, b, tmp);
	mp_int_mod(tmp, p, res);
	mp_clear_free(tmp);
}