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
 int /*<<< orphan*/  multiorder_join1 (int,int,int) ; 
 int /*<<< orphan*/  multiorder_join2 (int,int) ; 
 int /*<<< orphan*/  multiorder_join3 (int) ; 

__attribute__((used)) static void multiorder_join(void)
{
	int i, j, idx;

	for (idx = 0; idx < 1024; idx = idx * 2 + 3) {
		for (i = 1; i < 15; i++) {
			for (j = 0; j < i; j++) {
				multiorder_join1(idx, i, j);
			}
		}
	}

	for (i = 1; i < 15; i++) {
		for (j = 0; j < i; j++) {
			multiorder_join2(i, j);
		}
	}

	for (i = 3; i < 10; i++) {
		multiorder_join3(i);
	}
}