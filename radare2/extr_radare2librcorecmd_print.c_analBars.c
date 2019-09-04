#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_5__ {int size; } ;
typedef  int /*<<< orphan*/  RCore ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_MASK_BASIC ; 
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 scalar_t__ checkAnalType (TYPE_1__*,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  matchBar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_anal_op_free (TYPE_1__*) ; 
 scalar_t__ r_cons_is_breaked () ; 
 TYPE_1__* r_core_anal_op (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut8 *analBars(RCore *core, int type, int nblocks, int blocksize, int skipblocks, ut64 from) {
	ut8 *p;
	int j, i = 0;
	ut8 *ptr = calloc (1, nblocks);
	if (!ptr) {
		eprintf ("Error: failed to malloc memory");
		return NULL;
	}
	p = malloc (blocksize);
	if (!p) {
		R_FREE (ptr);
		eprintf ("Error: failed to malloc memory");
		return NULL;
	}
	for (i = 0; i < nblocks; i++) {
		if (r_cons_is_breaked ()) {
			break;
		}
		ut64 off = from + (i + skipblocks) * blocksize;
		for (j = 0; j < blocksize ; j++) {
			RAnalOp *op = r_core_anal_op (core, off + j, R_ANAL_OP_MASK_BASIC);
			if (op) {
				if (op->size < 1) {
					// do nothing
					if (type == 'i') {
						matchBar (ptr, i);
					}
				} else {
					if (checkAnalType (op, type)) {
						matchBar (ptr, i);
					}
				}
				if (op->size > 0) {
					j += op->size - 1;
				}
				r_anal_op_free (op);
			} else {
				if (type == 'i') {
					matchBar (ptr, i);
				}
			}
		}
	}
	free (p);
	return ptr;
}