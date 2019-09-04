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
typedef  int /*<<< orphan*/  u64 ;
struct ce_array {int n; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (void*,void*,int) ; 

__attribute__((used)) static void del_elem(struct ce_array *ca, int idx)
{
	/* Save us a function call when deleting the last element. */
	if (ca->n - (idx + 1))
		memmove((void *)&ca->array[idx],
			(void *)&ca->array[idx + 1],
			(ca->n - (idx + 1)) * sizeof(u64));

	ca->n--;
}