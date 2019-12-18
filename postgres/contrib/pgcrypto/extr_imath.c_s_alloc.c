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
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill ; 
 int /*<<< orphan*/ * px_alloc (int) ; 

__attribute__((used)) static mp_digit *
s_alloc(mp_size num)
{
	mp_digit   *out = px_alloc(num * sizeof(mp_digit));

	assert(out != NULL);

#if IMATH_DEBUG
	for (mp_size ix = 0; ix < num; ++ix)
		out[ix] = fill;
#endif
	return out;
}