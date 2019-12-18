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
struct state {struct arc* outs; } ;
struct arc {int type; scalar_t__ co; struct arc* outchain; } ;
typedef  scalar_t__ color ;

/* Variables and functions */

__attribute__((used)) static struct arc *
findarc(struct state *s,
		int type,
		color co)
{
	struct arc *a;

	for (a = s->outs; a != NULL; a = a->outchain)
		if (a->type == type && a->co == co)
			return a;
	return NULL;
}