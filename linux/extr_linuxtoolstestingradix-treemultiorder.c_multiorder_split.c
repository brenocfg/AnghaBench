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
 int /*<<< orphan*/  __multiorder_split (int,int) ; 
 int /*<<< orphan*/  __multiorder_split2 (int,int) ; 
 int /*<<< orphan*/  __multiorder_split3 (int,int) ; 

__attribute__((used)) static void multiorder_split(void)
{
	int i, j;

	for (i = 3; i < 11; i++)
		for (j = 0; j < i; j++) {
			__multiorder_split(i, j);
			__multiorder_split2(i, j);
			__multiorder_split3(i, j);
		}
}