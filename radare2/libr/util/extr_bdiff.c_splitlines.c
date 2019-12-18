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
struct line {int h; int len; char const* l; int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static int splitlines(const char *a, int len, struct line **lr) {
	int h, i;
	const char *p, *b = a;
	const char * const plast = a + len - 1;
	struct line *l;

	if (!a) {
		eprintf ("null pointer received\n");
		return 0;
	}

	/* count the lines */
	i = 1; /* extra line for sentinel */
	for (p = a; p < a + len; p++) {
		if (*p == '\n' || p == plast) {
			i++;
		}
	}

	*lr = l = (struct line *)malloc(sizeof(struct line) * i);
	if (!l) {
		return -1;
	}

	/* build the line array and calculate hashes */
	h = 0;
	for (p = a; p < a + len; p++) {
		/* Leonid Yuriev's hash */
		h = (h * 1664525) + *p + 1013904223;

		if (*p == '\n' || p == plast) {
			l->h = h;
			h = 0;
			l->len = p - b + 1;
			l->l = b;
			l->n = INT_MAX;
			l++;
			b = p + 1;
		}
	}

	/* set up a sentinel */
	l->h = l->len = 0;
	l->l = a + len;
	return i - 1;
}