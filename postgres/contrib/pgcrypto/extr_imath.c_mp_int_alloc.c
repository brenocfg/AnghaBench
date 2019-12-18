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
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  mp_int_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * px_alloc (int) ; 

mp_int
mp_int_alloc(void)
{
	mp_int		out = px_alloc(sizeof(mpz_t));

	if (out != NULL)
		mp_int_init(out);

	return out;
}