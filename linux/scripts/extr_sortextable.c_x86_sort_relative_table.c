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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  compare_relative_table ; 
 int /*<<< orphan*/  qsort (char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void x86_sort_relative_table(char *extab_image, int image_size)
{
	int i;

	i = 0;
	while (i < image_size) {
		uint32_t *loc = (uint32_t *)(extab_image + i);

		w(r(loc) + i, loc);
		w(r(loc + 1) + i + 4, loc + 1);
		w(r(loc + 2) + i + 8, loc + 2);

		i += sizeof(uint32_t) * 3;
	}

	qsort(extab_image, image_size / 12, 12, compare_relative_table);

	i = 0;
	while (i < image_size) {
		uint32_t *loc = (uint32_t *)(extab_image + i);

		w(r(loc) - i, loc);
		w(r(loc + 1) - (i + 4), loc + 1);
		w(r(loc + 2) - (i + 8), loc + 2);

		i += sizeof(uint32_t) * 3;
	}
}