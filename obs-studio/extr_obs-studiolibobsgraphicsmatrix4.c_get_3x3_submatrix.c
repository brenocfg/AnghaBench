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
struct matrix4 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void get_3x3_submatrix(float *dst, const struct matrix4 *m,
		int i, int j)
{
	const float *mf = (const float *)m;
	int ti, tj, idst, jdst;

	for (ti = 0; ti < 4; ti++) {
		if (ti < i)
			idst = ti;
		else if (ti > i)
			idst = ti-1;
		else
			continue;

		for (tj = 0; tj < 4; tj++) {
			if (tj < j)
				jdst = tj;
			else if (tj > j)
				jdst = tj-1;
			else
				continue;

			dst[(idst*3) + jdst] = mf[(ti*4) + tj];
		}
	}
}