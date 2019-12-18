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
 int /*<<< orphan*/  GFP_KERNEL ; 
 void** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

void **__memcat_p(void **a, void **b)
{
	void **p = a, **new;
	int nr;

	/* count the elements in both arrays */
	for (nr = 0, p = a; *p; nr++, p++)
		;
	for (p = b; *p; nr++, p++)
		;
	/* one for the NULL-terminator */
	nr++;

	new = kmalloc_array(nr, sizeof(void *), GFP_KERNEL);
	if (!new)
		return NULL;

	/* nr -> last index; p points to NULL in b[] */
	for (nr--; nr >= 0; nr--, p = p == b ? &a[nr] : p - 1)
		new[nr] = *p;

	return new;
}