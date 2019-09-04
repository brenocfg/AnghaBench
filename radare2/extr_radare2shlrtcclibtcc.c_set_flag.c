#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int flags; int offset; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  TCCState ;
typedef  TYPE_1__ FlagDef ;

/* Variables and functions */
 int FD_INVERT ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int set_flag(TCCState *s, const FlagDef *flags, int nb_flags,
		     const char *name, int value)
{
	int i;
	const FlagDef *p;
	const char *r;

	r = name;
	if (r[0] == 'n' && r[1] == 'o' && r[2] == '-') {
		r += 3;
		value = !value;
	}
	for (i = 0, p = flags; i < nb_flags; i++, p++) {
		if (!strcmp (r, p->name)) {
			goto found;
		}
	}
	return -1;
found:
	if (p->flags & FD_INVERT) {
		value = !value;
	}
	*(int *) ((uint8_t *) s + p->offset) = value;
	return 0;
}