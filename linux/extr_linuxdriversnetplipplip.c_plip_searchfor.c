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
 int PLIP_MAX ; 

__attribute__((used)) static inline int
plip_searchfor(int list[], int a)
{
	int i;
	for (i = 0; i < PLIP_MAX && list[i] != -1; i++) {
		if (list[i] == a) return 1;
	}
	return 0;
}