#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {float f; int /*<<< orphan*/  q; scalar_t__ d; int /*<<< orphan*/  s; } ;
struct r_magic {int type; int vallen; char reln; TYPE_1__ value; } ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ RMagic ;

/* Variables and functions */
#define  FILE_BEDOUBLE 139 
#define  FILE_BEFLOAT 138 
#define  FILE_BESTRING16 137 
#define  FILE_DOUBLE 136 
#define  FILE_FLOAT 135 
#define  FILE_LEDOUBLE 134 
#define  FILE_LEFLOAT 133 
#define  FILE_LESTRING16 132 
#define  FILE_PSTRING 131 
#define  FILE_REGEX 130 
#define  FILE_SEARCH 129 
#define  FILE_STRING 128 
 int R_MAGIC_CHECK ; 
 int /*<<< orphan*/  eatsize (char const**) ; 
 int /*<<< orphan*/  file_magwarn (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_signextend (TYPE_2__*,struct r_magic*,int /*<<< orphan*/ ) ; 
 char* getstr (TYPE_2__*,char const*,int /*<<< orphan*/ ,int,int*,int) ; 
 scalar_t__ strtod (char const*,char**) ; 
 float strtof (char const*,char**) ; 
 int /*<<< orphan*/  strtoull (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int getvalue(RMagic *ms, struct r_magic *m, const char **p, int action) {
	int slen;

	switch (m->type) {
	case FILE_BESTRING16:
	case FILE_LESTRING16:
	case FILE_STRING:
	case FILE_PSTRING:
	case FILE_REGEX:
	case FILE_SEARCH:
		*p = getstr(ms, *p, m->value.s, sizeof (m->value.s), &slen, action);
		if (!*p) {
			if (ms->flags & R_MAGIC_CHECK) {
				file_magwarn (ms, "cannot get string from `%s'",
					m->value.s);
			}
			return -1;
		}
		m->vallen = slen;
		if (m->type == FILE_PSTRING) {
			m->vallen++;
		}
		return 0;
	case FILE_FLOAT:
	case FILE_BEFLOAT:
	case FILE_LEFLOAT:
		if (m->reln != 'x') {
			char *ep;
#ifdef HAVE_STRTOF
			m->value.f = strtof(*p, &ep);
#else
			m->value.f = (float)strtod(*p, &ep);
#endif
			*p = ep;
		}
		return 0;
	case FILE_DOUBLE:
	case FILE_BEDOUBLE:
	case FILE_LEDOUBLE:
		if (m->reln != 'x') {
			char *ep;
			m->value.d = strtod(*p, &ep);
			*p = ep;
		}
		return 0;
	default:
		if (m->reln != 'x') {
			char *ep;
			m->value.q = file_signextend(ms, m,
			    (ut64)strtoull(*p, &ep, 0));
			*p = ep;
			eatsize(p);
		}
		return 0;
	}
}