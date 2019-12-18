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
typedef  scalar_t__ u32 ;
struct ebitmap_node {scalar_t__ startbit; int* maps; struct ebitmap_node* next; } ;
struct ebitmap {scalar_t__ highbit; struct ebitmap_node* node; } ;

/* Variables and functions */
 int EBITMAP_UNIT_NUMS ; 
 int EBITMAP_UNIT_SIZE ; 
 scalar_t__ __fls (int) ; 

int ebitmap_contains(struct ebitmap *e1, struct ebitmap *e2, u32 last_e2bit)
{
	struct ebitmap_node *n1, *n2;
	int i;

	if (e1->highbit < e2->highbit)
		return 0;

	n1 = e1->node;
	n2 = e2->node;

	while (n1 && n2 && (n1->startbit <= n2->startbit)) {
		if (n1->startbit < n2->startbit) {
			n1 = n1->next;
			continue;
		}
		for (i = EBITMAP_UNIT_NUMS - 1; (i >= 0) && !n2->maps[i]; )
			i--;	/* Skip trailing NULL map entries */
		if (last_e2bit && (i >= 0)) {
			u32 lastsetbit = n2->startbit + i * EBITMAP_UNIT_SIZE +
					 __fls(n2->maps[i]);
			if (lastsetbit > last_e2bit)
				return 0;
		}

		while (i >= 0) {
			if ((n1->maps[i] & n2->maps[i]) != n2->maps[i])
				return 0;
			i--;
		}

		n1 = n1->next;
		n2 = n2->next;
	}

	if (n2)
		return 0;

	return 1;
}