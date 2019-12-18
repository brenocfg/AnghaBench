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
struct TYPE_3__ {int /*<<< orphan*/  constpool; int /*<<< orphan*/  attr; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_1__ RConsCanvas ;

/* Variables and functions */
 scalar_t__ __isAnsiSequence (char const*) ; 
 int /*<<< orphan*/  r_str_constpool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_append_n (int /*<<< orphan*/ *,char const*,int const) ; 
 int /*<<< orphan*/  r_strbuf_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *set_attr(RConsCanvas *c, const char *s) {
	if (!c || !s) {
		return NULL;
	}
	const char *p = s;

	while (__isAnsiSequence (p)) {
		p += 2;
		while (*p && *p != 'J' && *p != 'm' && *p != 'H') {
			p++;
		}
		p++;
	}

	const int slen = p - s;
	if (slen > 0) {
		RStrBuf tmp;
		r_strbuf_init (&tmp);
		r_strbuf_append_n (&tmp, s, slen);
		c->attr = r_str_constpool_get (&c->constpool, r_strbuf_get (&tmp));
		r_strbuf_fini (&tmp);
	}
	return p;
}