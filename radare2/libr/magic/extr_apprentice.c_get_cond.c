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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
#define  COND_ELIF 131 
#define  COND_ELSE 130 
#define  COND_IF 129 
#define  COND_NONE 128 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static int get_cond(const char *l, const char **t) {
	const struct cond_tbl_s *p;
	static const struct cond_tbl_s {
		char name[8];
		size_t len;
		int cond;
	} cond_tbl[] = {
		{ "if",		2,	COND_IF },
		{ "elif",	4,	COND_ELIF },
		{ "else",	4,	COND_ELSE },
		{ "",		0,	COND_NONE },
	};

	for (p = cond_tbl; p->len; p++) {
		if (strncmp (l, p->name, p->len) == 0 &&
				isspace ((ut8)l[p->len])) {
			if (t) {
				*t = l + p->len;
			}
			break;
		}
	}
	return p->cond;
}