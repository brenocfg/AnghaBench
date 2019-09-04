#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* attr; int attrslen; TYPE_1__* attrs; int /*<<< orphan*/  color; } ;
struct TYPE_5__ {int loc; char* a; } ;
typedef  TYPE_2__ RConsCanvas ;

/* Variables and functions */
 char** attr_at (TYPE_2__*,int) ; 

__attribute__((used)) static void stamp_attr(RConsCanvas *c, int loc, int length) {
	if (!c->color) {
		return;
	}
	int i;
	const char **s;
	s = attr_at (c, loc);

	if (s) {
#if 0
		if (*s != 0 && strlen (*s) > 2 && *(*s + 2) == '0') {
			if (strlen (c->attr) == 5 && *(c->attr + 2) != '0') {
				char tmp[9];
				memcpy (tmp, c->attr, 2);
				strcpy (tmp + 2, "0;");
				memcpy (tmp + 4, c->attr + 2, 3);
				tmp[8] = 0;
				c->attr = r_str_const (tmp);
			}
		}
#endif
		*s = c->attr;
	} else {
		for (i = c->attrslen; i > 0 && loc < c->attrs[i - 1].loc; i--) {
			c->attrs[i] = c->attrs[i - 1];
		}
		c->attrs[i].loc = loc;
		c->attrs[i].a = c->attr;
		c->attrslen++;
	}

	for (i = 1; i < length; i++) {
		s = attr_at (c, loc + i);
		if (s) {
			*s = 0;
		}
	}
}