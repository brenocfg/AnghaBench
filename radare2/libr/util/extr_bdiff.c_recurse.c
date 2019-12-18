#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pos {int dummy; } ;
struct line {int dummy; } ;
struct hunklist {TYPE_1__* head; } ;
struct TYPE_2__ {int a1; int a2; int b1; int b2; } ;

/* Variables and functions */
 int longest_match (struct line*,struct line*,struct pos*,int,int,int,int,int*,int*) ; 

__attribute__((used)) static void recurse(struct line *a, struct line *b, struct pos *pos,
		    int a1, int a2, int b1, int b2, struct hunklist *l)
{
	int i, j, k;

	/* find the longest match in this chunk */
	k = longest_match(a, b, pos, a1, a2, b1, b2, &i, &j);
	if (!k) {
		return;
	}

	/* and recurse on the remaining chunks on either side */
	recurse(a, b, pos, a1, i, b1, j, l);
	l->head->a1 = i;
	l->head->a2 = i + k;
	l->head->b1 = j;
	l->head->b2 = j + k;
	l->head++;
	recurse(a, b, pos, i + k, a2, j + k, b2, l);
}