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
typedef  size_t mp_size ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * px_realloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * s_alloc (size_t) ; 

__attribute__((used)) static mp_digit *
s_realloc(mp_digit *old, mp_size osize, mp_size nsize)
{
#if IMATH_DEBUG
	mp_digit   *new = s_alloc(nsize);

	assert(new != NULL);

	for (mp_size ix = 0; ix < nsize; ++ix)
		new[ix] = fill;
	memcpy(new, old, osize * sizeof(mp_digit));
#else
	mp_digit   *new = px_realloc(old, nsize * sizeof(mp_digit));

	assert(new != NULL);
#endif

	return new;
}