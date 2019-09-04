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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 struct label* malloc (int) ; 
 int rd_label (char const**,int*,struct label**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp ; 
 char* strchr (char const*,char const) ; 

__attribute__((used)) static void readlabel(const char **p, int store) {
	const char *c, *d, *pos, *dummy;
	int i, j;
	struct label *buf, *previous;
	for (d = *p; *d && *d != ';'; ++d) {
		;
	}
	for (c = *p; !strchr (" \r\n\t", *c) && c < d; ++c) {
		;
	}
	pos = strchr (*p, ':');
	if (!pos || pos >= c) {
		return;
	}
	if (pos == *p) {
		eprintf ("`:' found without a label");
		return;
	}
	if (!store) {
		*p = pos + 1;
		return;
	}
	c = pos + 1;
	dummy = *p;
	j = rd_label (&dummy, &i, &previous, sp, 0);
	if (i || j) {
		eprintf ("duplicate definition of label %s\n", *p);
		*p = c;
		return;
	}
	if (!(buf = malloc (sizeof (struct label) + c - *p))) {
		eprintf ("not enough memory to store label %s\n", *p);
#if 0
		*p = c;
		return;
	}
	// not used and dead code.
	// originally it was saved into lastlabel value.
	// now only leaks bytes.
	strncpy (buf->name, *p, c - *p - 1);
	buf->name[c - *p - 1] = 0;
	*p = c;
	buf->value = addr;
	// lastlabel = buf;
	if (previous) {
		buf->next = previous->next;
	} else {
		buf->next = NULL;
	}
	buf->prev = previous;
	buf->valid = 1;
	buf->busy = 0;
	buf->ref = NULL;
	if (buf->prev) {
		buf->prev->next = buf;
	}
	if (buf->next) {
		buf->next->prev = buf;
	}
	// leaks here since buf is not used.
#else
	}
	*p = c;
#endif
}