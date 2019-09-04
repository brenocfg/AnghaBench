#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct match {scalar_t__ st; scalar_t__ fresh; scalar_t__ tmp; char* beginp; char* endp; int eflags; char* coldp; TYPE_1__* g; } ;
typedef  scalar_t__ states ;
typedef  int /*<<< orphan*/  sopno ;
struct TYPE_2__ {int cflags; int nbol; scalar_t__ neol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN (scalar_t__,scalar_t__) ; 
 int BOL ; 
 int BOLEOL ; 
 int BOW ; 
 int /*<<< orphan*/  CLEAR (scalar_t__) ; 
 int EOL ; 
 int EOW ; 
 int /*<<< orphan*/  EQ (scalar_t__,scalar_t__) ; 
 scalar_t__ ISSET (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ISWORD (int) ; 
 int NOTHING ; 
 char OUT ; 
 int R_REGEX_NEWLINE ; 
 int R_REGEX_NOTBOL ; 
 int R_REGEX_NOTEOL ; 
 int /*<<< orphan*/  SET1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SP (char*,scalar_t__,int) ; 
 scalar_t__ step (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static char *			/* where tentative match ended, or NULL */
fast(struct match *m, char *start, char *stop, sopno startst, sopno stopst)
{
	states st = m->st;
	states fresh = m->fresh;
	states tmp = m->tmp;
	char *p = start;
	int c = (start == m->beginp) ? OUT : *(start-1);
	int lastc;	/* previous c */
	int flagch;
	int i;
	char *coldp;	/* last p after which no match was underway */

	CLEAR(st);
	SET1(st, startst);
	st = step(m->g, startst, stopst, st, NOTHING, st);
	ASSIGN(fresh, st);
	SP("start", st, *p);
	coldp = NULL;
	for (;;) {
		/* next character */
		lastc = c;
		c = (p == m->endp) ? OUT : *p;
		if (st==fresh)
			coldp = p;

		/* is there an EOL and/or BOL between lastc and c? */
		flagch = '\0';
		i = 0;
		if ( (lastc == '\n' && m->g->cflags&R_REGEX_NEWLINE) ||
				(lastc == OUT && !(m->eflags&R_REGEX_NOTBOL)) ) {
			flagch = BOL;
			i = m->g->nbol;
		}
		if ( (c == '\n' && m->g->cflags&R_REGEX_NEWLINE) ||
				(c == OUT && !(m->eflags&R_REGEX_NOTEOL)) ) {
			flagch = (flagch == BOL) ? BOLEOL : EOL;
			i += m->g->neol;
		}
		if (i != 0) {
			for (; i > 0; i--)
				st = step(m->g, startst, stopst, st, flagch, st);
			SP("boleol", st, c);
		}

		/* how about a word boundary? */
		if ( (flagch == BOL || (lastc != OUT && !ISWORD(lastc))) &&
					(c != OUT && ISWORD(c)) ) {
			flagch = BOW;
		}
		if ( (lastc != OUT && ISWORD(lastc)) &&
				(flagch == EOL || (c != OUT && !ISWORD(c))) ) {
			flagch = EOW;
		}
		if (flagch == BOW || flagch == EOW) {
			st = step(m->g, startst, stopst, st, flagch, st);
			SP("boweow", st, c);
		}

		/* are we done? */
		if (ISSET(st, stopst) || p == stop)
			break;		/* NOTE BREAK OUT */

		/* no, we must deal with this character */
		ASSIGN(tmp, st);
		ASSIGN(st, fresh);
		if (c == OUT) {
			break;
		}
		st = step(m->g, startst, stopst, tmp, c, st);
		SP("aft", st, c);
		if (!EQ(step(m->g, startst, stopst, st, NOTHING, st), st)) {
			break;
		}
		p++;
	}

	if (coldp) {
		m->coldp = coldp;
		if (ISSET(st, stopst))
			return(p+1);
	}
	return NULL;
}