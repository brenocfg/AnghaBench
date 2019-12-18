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
 int get_random_int () ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int *get_random_order(int count)
{
	int *order;
	int n, r, tmp;

	order = kmalloc_array(count, sizeof(*order), GFP_KERNEL);
	if (!order)
		return order;

	for (n = 0; n < count; n++)
		order[n] = n;

	for (n = count - 1; n > 1; n--) {
		r = get_random_int() % (n + 1);
		if (r != n) {
			tmp = order[n];
			order[n] = order[r];
			order[r] = tmp;
		}
	}

	return order;
}