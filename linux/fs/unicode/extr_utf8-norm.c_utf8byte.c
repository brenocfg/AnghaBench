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
typedef  int /*<<< orphan*/  utf8leaf_t ;
struct utf8cursor {char* p; char* s; scalar_t__ len; int ccc; int nccc; scalar_t__ sp; int* ss; scalar_t__ slen; int /*<<< orphan*/  hangul; TYPE_1__* data; } ;
struct TYPE_3__ {scalar_t__ maxage; } ;

/* Variables and functions */
 int DECOMPOSE ; 
 int LEAF_CCC (int /*<<< orphan*/ *) ; 
 size_t LEAF_GEN (int /*<<< orphan*/ *) ; 
 int* LEAF_STR (int /*<<< orphan*/ *) ; 
 int MAXCCC ; 
 int MINCCC ; 
 int STOPPER ; 
 scalar_t__* utf8agetab ; 
 scalar_t__ utf8clen (int*) ; 
 int /*<<< orphan*/ * utf8lookup (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * utf8nlookup (TYPE_1__*,int /*<<< orphan*/ ,int*,scalar_t__) ; 

int utf8byte(struct utf8cursor *u8c)
{
	utf8leaf_t *leaf;
	int ccc;

	for (;;) {
		/* Check for the end of a decomposed character. */
		if (u8c->p && *u8c->s == '\0') {
			u8c->s = u8c->p;
			u8c->p = NULL;
		}

		/* Check for end-of-string. */
		if (!u8c->p && (u8c->len == 0 || *u8c->s == '\0')) {
			/* There is no next byte. */
			if (u8c->ccc == STOPPER)
				return 0;
			/* End-of-string during a scan counts as a stopper. */
			ccc = STOPPER;
			goto ccc_mismatch;
		} else if ((*u8c->s & 0xC0) == 0x80) {
			/* This is a continuation of the current character. */
			if (!u8c->p)
				u8c->len--;
			return (unsigned char)*u8c->s++;
		}

		/* Look up the data for the current character. */
		if (u8c->p) {
			leaf = utf8lookup(u8c->data, u8c->hangul, u8c->s);
		} else {
			leaf = utf8nlookup(u8c->data, u8c->hangul,
					   u8c->s, u8c->len);
		}

		/* No leaf found implies that the input is a binary blob. */
		if (!leaf)
			return -1;

		ccc = LEAF_CCC(leaf);
		/* Characters that are too new have CCC 0. */
		if (utf8agetab[LEAF_GEN(leaf)] > u8c->data->maxage) {
			ccc = STOPPER;
		} else if (ccc == DECOMPOSE) {
			u8c->len -= utf8clen(u8c->s);
			u8c->p = u8c->s + utf8clen(u8c->s);
			u8c->s = LEAF_STR(leaf);
			/* Empty decomposition implies CCC 0. */
			if (*u8c->s == '\0') {
				if (u8c->ccc == STOPPER)
					continue;
				ccc = STOPPER;
				goto ccc_mismatch;
			}

			leaf = utf8lookup(u8c->data, u8c->hangul, u8c->s);
			if (!leaf)
				return -1;
			ccc = LEAF_CCC(leaf);
		}

		/*
		 * If this is not a stopper, then see if it updates
		 * the next canonical class to be emitted.
		 */
		if (ccc != STOPPER && u8c->ccc < ccc && ccc < u8c->nccc)
			u8c->nccc = ccc;

		/*
		 * Return the current byte if this is the current
		 * combining class.
		 */
		if (ccc == u8c->ccc) {
			if (!u8c->p)
				u8c->len--;
			return (unsigned char)*u8c->s++;
		}

		/* Current combining class mismatch. */
ccc_mismatch:
		if (u8c->nccc == STOPPER) {
			/*
			 * Scan forward for the first canonical class
			 * to be emitted.  Save the position from
			 * which to restart.
			 */
			u8c->ccc = MINCCC - 1;
			u8c->nccc = ccc;
			u8c->sp = u8c->p;
			u8c->ss = u8c->s;
			u8c->slen = u8c->len;
			if (!u8c->p)
				u8c->len -= utf8clen(u8c->s);
			u8c->s += utf8clen(u8c->s);
		} else if (ccc != STOPPER) {
			/* Not a stopper, and not the ccc we're emitting. */
			if (!u8c->p)
				u8c->len -= utf8clen(u8c->s);
			u8c->s += utf8clen(u8c->s);
		} else if (u8c->nccc != MAXCCC + 1) {
			/* At a stopper, restart for next ccc. */
			u8c->ccc = u8c->nccc;
			u8c->nccc = MAXCCC + 1;
			u8c->s = u8c->ss;
			u8c->p = u8c->sp;
			u8c->len = u8c->slen;
		} else {
			/* All done, proceed from here. */
			u8c->ccc = STOPPER;
			u8c->nccc = STOPPER;
			u8c->sp = NULL;
			u8c->ss = NULL;
			u8c->slen = 0;
		}
	}
}