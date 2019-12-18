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
typedef  int u16 ;

/* Variables and functions */
 int* hfsplus_compose_table ; 

__attribute__((used)) static u16 *hfsplus_compose_lookup(u16 *p, u16 cc)
{
	int i, s, e;

	s = 1;
	e = p[1];
	if (!e || cc < p[s * 2] || cc > p[e * 2])
		return NULL;
	do {
		i = (s + e) / 2;
		if (cc > p[i * 2])
			s = i + 1;
		else if (cc < p[i * 2])
			e = i - 1;
		else
			return hfsplus_compose_table + p[i * 2 + 1];
	} while (s <= e);
	return NULL;
}