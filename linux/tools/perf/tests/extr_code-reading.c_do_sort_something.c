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
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_sort_something(void)
{
	int buf[40960], i;

	for (i = 0; i < (int)ARRAY_SIZE(buf); i++)
		buf[i] = ARRAY_SIZE(buf) - i - 1;

	qsort(buf, ARRAY_SIZE(buf), sizeof(int), comp);

	for (i = 0; i < (int)ARRAY_SIZE(buf); i++) {
		if (buf[i] != i) {
			pr_debug("qsort failed\n");
			break;
		}
	}
}