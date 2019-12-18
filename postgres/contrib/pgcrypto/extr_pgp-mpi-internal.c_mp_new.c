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
 int /*<<< orphan*/ * mp_int_alloc () ; 
 int /*<<< orphan*/  mp_int_init_size (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static mpz_t *
mp_new()
{
	mpz_t	   *mp = mp_int_alloc();

	mp_int_init_size(mp, 256);
	return mp;
}