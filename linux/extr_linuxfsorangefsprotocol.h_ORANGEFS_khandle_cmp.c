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
struct orangefs_khandle {scalar_t__* u; } ;

/* Variables and functions */

__attribute__((used)) static inline int ORANGEFS_khandle_cmp(const struct orangefs_khandle *kh1,
				   const struct orangefs_khandle *kh2)
{
	int i;

	for (i = 15; i >= 0; i--) {
		if (kh1->u[i] > kh2->u[i])
			return 1;
		if (kh1->u[i] < kh2->u[i])
			return -1;
	}

	return 0;
}