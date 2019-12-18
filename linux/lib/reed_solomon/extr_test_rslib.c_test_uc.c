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
typedef  int /*<<< orphan*/  uint16_t ;
struct wspace {int* derrlocs; int* errlocs; int /*<<< orphan*/ * s; int /*<<< orphan*/ * r; int /*<<< orphan*/ * c; int /*<<< orphan*/ * corr; } ;
struct rs_control {TYPE_1__* codec; } ;
struct estat {int nwords; int /*<<< orphan*/  dwrong; int /*<<< orphan*/  wepos; int /*<<< orphan*/  irv; } ;
struct TYPE_2__ {int nroots; } ;

/* Variables and functions */
#define  CALLER_SYNDROME 130 
#define  CORR_BUFFER 129 
#define  IN_PLACE 128 
 int /*<<< orphan*/  compute_syndrome (struct rs_control*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int decode_rs16 (struct rs_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fix_err (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int get_rcw_we (struct rs_control*,struct wspace*,int,int,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_uc(struct rs_control *rs, int len, int errs,
		int eras, int trials, struct estat *stat,
		struct wspace *ws, int method)
{
	int dlen = len - rs->codec->nroots;
	int *derrlocs = ws->derrlocs;
	int *errlocs = ws->errlocs;
	uint16_t *corr = ws->corr;
	uint16_t *c = ws->c;
	uint16_t *r = ws->r;
	uint16_t *s = ws->s;
	int derrs, nerrs;
	int i, j;

	for (j = 0; j < trials; j++) {
		nerrs = get_rcw_we(rs, ws, len, errs, eras);

		switch (method) {
		case CORR_BUFFER:
			derrs = decode_rs16(rs, r, r + dlen, dlen,
					NULL, eras, derrlocs, 0, corr);
			fix_err(r, derrs, corr, derrlocs);
			break;
		case CALLER_SYNDROME:
			compute_syndrome(rs, r, len, s);
			derrs = decode_rs16(rs, NULL, NULL, dlen,
					s, eras, derrlocs, 0, corr);
			fix_err(r, derrs, corr, derrlocs);
			break;
		case IN_PLACE:
			derrs = decode_rs16(rs, r, r + dlen, dlen,
					NULL, eras, derrlocs, 0, NULL);
			break;
		default:
			continue;
		}

		if (derrs != nerrs)
			stat->irv++;

		if (method != IN_PLACE) {
			for (i = 0; i < derrs; i++) {
				if (errlocs[derrlocs[i]] != 1)
					stat->wepos++;
			}
		}

		if (memcmp(r, c, len * sizeof(*r)))
			stat->dwrong++;
	}
	stat->nwords += trials;
}