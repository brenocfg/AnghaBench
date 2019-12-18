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
typedef  int uint16_t ;
struct wspace {int* derrlocs; int* errlocs; int* c; int* r; } ;
struct rs_control {TYPE_1__* codec; } ;
struct TYPE_2__ {int nroots; int nn; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_rs16 (struct rs_control*,int*,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ ewsc ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int prandom_u32 () ; 

__attribute__((used)) static int get_rcw_we(struct rs_control *rs, struct wspace *ws,
			int len, int errs, int eras)
{
	int nroots = rs->codec->nroots;
	int *derrlocs = ws->derrlocs;
	int *errlocs = ws->errlocs;
	int dlen = len - nroots;
	int nn = rs->codec->nn;
	uint16_t *c = ws->c;
	uint16_t *r = ws->r;
	int errval;
	int errloc;
	int i;

	/* Load c with random data and encode */
	for (i = 0; i < dlen; i++)
		c[i] = prandom_u32() & nn;

	memset(c + dlen, 0, nroots * sizeof(*c));
	encode_rs16(rs, c, dlen, c + dlen, 0);

	/* Make copyand add errors and erasures */
	memcpy(r, c, len * sizeof(*r));
	memset(errlocs, 0, len * sizeof(*errlocs));
	memset(derrlocs, 0, nroots * sizeof(*derrlocs));

	/* Generating random errors */
	for (i = 0; i < errs; i++) {
		do {
			/* Error value must be nonzero */
			errval = prandom_u32() & nn;
		} while (errval == 0);

		do {
			/* Must not choose the same location twice */
			errloc = prandom_u32() % len;
		} while (errlocs[errloc] != 0);

		errlocs[errloc] = 1;
		r[errloc] ^= errval;
	}

	/* Generating random erasures */
	for (i = 0; i < eras; i++) {
		do {
			/* Must not choose the same location twice */
			errloc = prandom_u32() % len;
		} while (errlocs[errloc] != 0);

		derrlocs[i] = errloc;

		if (ewsc && (prandom_u32() & 1)) {
			/* Erasure with the symbol intact */
			errlocs[errloc] = 2;
		} else {
			/* Erasure with corrupted symbol */
			do {
				/* Error value must be nonzero */
				errval = prandom_u32() & nn;
			} while (errval == 0);

			errlocs[errloc] = 1;
			r[errloc] ^= errval;
			errs++;
		}
	}

	return errs;
}