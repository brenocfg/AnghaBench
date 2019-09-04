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
 char max (char,char) ; 

__attribute__((used)) static inline signed char TREEMAX(signed char *cp)
{
	signed char tmp1, tmp2;

	tmp1 = max(*(cp+2), *(cp+3));
	tmp2 = max(*(cp), *(cp+1));

	return max(tmp1, tmp2);
}