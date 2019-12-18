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

/* Variables and functions */
 int /*<<< orphan*/  VDSO__MAP_NAME ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ find_map (void**,void**,int /*<<< orphan*/ ) ; 
 size_t fwrite (void*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

int main(void)
{
	void *start, *end;
	size_t size, written;

	if (find_map(&start, &end, VDSO__MAP_NAME))
		return 1;

	size = end - start;

	while (size) {
		written = fwrite(start, 1, size, stdout);
		if (!written)
			return 1;
		start += written;
		size -= written;
	}

	if (fflush(stdout))
		return 1;

	return 0;
}