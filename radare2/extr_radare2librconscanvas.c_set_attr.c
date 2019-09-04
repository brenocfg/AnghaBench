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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;
typedef  TYPE_1__ RConsCanvas ;

/* Variables and functions */
 int R_MIN (int,int) ; 
 scalar_t__ _is_ansi_seq (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int const) ; 
 int /*<<< orphan*/  r_str_const (char*) ; 

__attribute__((used)) static const char *set_attr(RConsCanvas *c, const char *s) {
	if (!c || !s) {
		return NULL;
	}
	const char *p = s;

	while (_is_ansi_seq (p)) {
		p += 2;
		while (*p && *p != 'J' && *p != 'm' && *p != 'H') {
			p++;
		}
		p++;
	}

	if (p != s) {
		char tmp[256];
		const int slen = R_MIN (p - s, sizeof (tmp) - 1);
		if (slen > 0) {
			memcpy (tmp, s, slen);
			tmp[slen] = 0;
			// could be faster
			c->attr = r_str_const (tmp);
		}
	}
	return p;
}