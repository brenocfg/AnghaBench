#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULong ;
struct TYPE_4__ {int wds; scalar_t__* x; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */

__attribute__((used)) static int
cmp
#ifdef KR_headers
	(a, b) Bigint *a, *b;
#else
	(Bigint *a, Bigint *b)
#endif
{
	ULong *xa, *xa0, *xb, *xb0;
	int i, j;

	i = a->wds;
	j = b->wds;
#ifdef DEBUG
	if (i > 1 && !a->x[i-1])
		Bug("cmp called with a->x[a->wds-1] == 0");
	if (j > 1 && !b->x[j-1])
		Bug("cmp called with b->x[b->wds-1] == 0");
#endif
	if (i -= j)
		return i;
	xa0 = a->x;
	xa = xa0 + j;
	xb0 = b->x;
	xb = xb0 + j;
	for(;;) {
		if (*--xa != *--xb)
			return *xa < *xb ? -1 : 1;
		if (xa <= xa0)
			break;
		}
	return 0;
	}