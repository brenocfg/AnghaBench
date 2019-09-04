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
 void** kzalloc (int,int /*<<< orphan*/ ) ; 

void *rtw_malloc2d(int h, int w, int size)
{
	int j;
	void **a = kzalloc(h * sizeof(void *) + h * w * size, GFP_KERNEL);

	if (!a)
		goto out;

	for (j = 0; j < h; j++)
		a[j] = ((char *)(a + h)) + j * w * size;
out:
	return a;
}