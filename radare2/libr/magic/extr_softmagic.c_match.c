#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  size_t ut32 ;
struct r_magic {int flag; scalar_t__ cont_level; int offset; char reln; scalar_t__ cond; int /*<<< orphan*/  type; int /*<<< orphan*/  lineno; } ;
struct TYPE_12__ {TYPE_1__* li; } ;
struct TYPE_13__ {int offset; int flags; TYPE_2__ c; int /*<<< orphan*/  line; } ;
struct TYPE_11__ {int off; int last_match; int got_match; } ;
typedef  TYPE_3__ RMagic ;

/* Variables and functions */
 int BINTEST ; 
 scalar_t__ COND_ELIF ; 
 scalar_t__ COND_ELSE ; 
 int /*<<< orphan*/  FILE_DEFAULT ; 
 int NOSPACE ; 
 int OFFADD ; 
 int R_MAGIC_CONTINUE ; 
 scalar_t__* R_MAGIC_DESC ; 
 int file_check_mem (TYPE_3__*,unsigned int) ; 
 int file_printf (TYPE_3__*,char*) ; 
 int magiccheck (TYPE_3__*,struct r_magic*) ; 
 int /*<<< orphan*/  mget (TYPE_3__*,int /*<<< orphan*/  const*,struct r_magic*,size_t,unsigned int) ; 
 int mprint (TYPE_3__*,struct r_magic*) ; 
 int print_sep (TYPE_3__*,int) ; 

__attribute__((used)) static int match(RMagic *ms, struct r_magic *magic, ut32 nmagic, const ut8 *s, size_t nbytes, int mode) {
	ut32 magindex = 0;
	unsigned int cont_level = 0;
	int need_separator = 0;
	int returnval = 0; /* if a match is found it is set to 1*/
	int firstline = 1; /* a flag to print X\n  X\n- X */
	int printed_something = 0;

	if (file_check_mem (ms, cont_level) == -1) {
		return -1;
	}
	for (magindex = 0; magindex < nmagic; magindex++) {
		int flush;
		struct r_magic *m = &magic[magindex];

		if ((m->flag & BINTEST) != mode) {
			/* Skip sub-tests */
			while (magic[magindex + 1].cont_level != 0 && ++magindex < nmagic - 1) {
				continue;
			}
			continue; /* Skip to next top-level test*/
		}

		ms->offset = m->offset;
		ms->line = m->lineno;

		/* if main entry matches, print it... */
		flush = !mget(ms, s, m, nbytes, cont_level);
		if (flush) {
			if (m->reln == '!') {
				flush = 0;
			}
		} else {
			int ret = magiccheck (ms, m);
			if (ret == -1) {
				return -1;
			}
			if (!ret) {
				flush++;
			}
		}
		if (flush) {
			/*
			 * main entry didn't match,
			 * flush its continuations
			 */
			while (magindex < nmagic - 1 && magic[magindex + 1].cont_level) {
				magindex++;
			}
			continue;
		}

		/*
		 * If we are going to print something, we'll need to print
		 * a blank before we print something else.
		 */
		if (*R_MAGIC_DESC) {
			need_separator = 1;
			printed_something = 1;
			if (print_sep (ms, firstline) == -1) {
				return -1;
			}
		}

		if ((ms->c.li[cont_level].off = mprint (ms, m)) == -1) {
			return -1;
		}

		/* and any continuations that match */
		if (file_check_mem(ms, ++cont_level) == -1) {
			return -1;
		}

		while (++magindex < nmagic - 1 && magic[magindex].cont_level != 0) {
			m = &magic[magindex];
			ms->line = m->lineno; /* for messages */

			if (cont_level < m->cont_level) {
				continue;
			}
			if (cont_level > m->cont_level) {
				/*
				 * We're at the end of the level
				 * "cont_level" continuations.
				 */
				cont_level = m->cont_level;
			}
			ms->offset = m->offset;
			if (m->flag & OFFADD) {
				ms->offset += ms->c.li[cont_level - 1].off;
			}

			if (m->cond == COND_ELSE || m->cond == COND_ELIF) {
				if (ms->c.li[cont_level].last_match == 1) {
					continue;
				}
			}
			flush = !mget(ms, s, m, nbytes, cont_level);
			if (flush && m->reln != '!') {
				continue;
			}

			switch (flush ? 1 : magiccheck(ms, m)) {
			case -1:
				return -1;
			case 0:
				ms->c.li[cont_level].last_match = 0;
				break;
			default:
				ms->c.li[cont_level].last_match = 1;
				if (m->type != FILE_DEFAULT) {
					ms->c.li[cont_level].got_match = 1;
				} else if (ms->c.li[cont_level].got_match) {
					ms->c.li[cont_level].got_match = 0;
					break;
				}
				/*
				 * If we are going to print something,
				 * make sure that we have a separator first.
				 */
				if (*R_MAGIC_DESC) {
					printed_something = 1;
					if (print_sep (ms, firstline) == -1) {
						return -1;
					}
				}
				/*
				 * This continuation matched.  Print
				 * its message, with a blank before it
				 * if the previous item printed and
				 * this item isn't empty.
				 */
				/* space if previous printed */
				if (need_separator
				    && ((m->flag & NOSPACE) == 0)
				    && *R_MAGIC_DESC) {
					if (file_printf (ms, " ") == -1) {
						return -1;
					}
					need_separator = 0;
				}
				if ((ms->c.li[cont_level].off = mprint (ms, m)) == -1) {
					return -1;
				}
				if (*R_MAGIC_DESC) {
					need_separator = 1;
				}

				/*
				 * If we see any continuations
				 * at a higher level,
				 * process them.
				 */
				if (file_check_mem (ms, ++cont_level) == -1) {
					return -1;
				}
				break;
			}
		}
		if (printed_something) {
			firstline = 0;
			returnval = 1;
		}
		if ((ms->flags & R_MAGIC_CONTINUE) == 0 && printed_something) {
			return 1; /* don't keep searching */
		}
	}
	return returnval;  /* This is hit if -k is set or there is no match */
}