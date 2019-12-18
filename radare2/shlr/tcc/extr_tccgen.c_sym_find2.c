#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int v; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */

Sym *sym_find2(Sym *s, int v) {
	while (s) {
		if (s->v == v) {
			return s;
		}
		s = s->prev;
	}
	return NULL;
}