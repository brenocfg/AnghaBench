#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_12__ {int bits; } ;
struct TYPE_11__ {scalar_t__ bits; scalar_t__ ptr; scalar_t__ jump; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  TYPE_1__ RAnalHint ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_MASK_BASIC ; 
 scalar_t__ UT64_MAX ; 
 int analop (TYPE_3__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* r_anal_hint_get (TYPE_3__*,scalar_t__) ; 
 TYPE_1__* r_anal_op_new () ; 

__attribute__((used)) static ut8 *anal_mask(RAnal *anal, int size, const ut8 *data, ut64 at) {
	RAnalOp *op = NULL;
	ut8 *ret = NULL;
	int oplen, idx = 0, obits = anal->bits;
	RAnalHint *hint = NULL;

	if (!data) {
		return NULL;
	}

	op = r_anal_op_new ();
	ret = malloc (size);
	memset (ret, 0xff, size);

	while (idx < size) {
		hint = r_anal_hint_get (anal, at + idx);
		if (hint) {
			if (hint->bits != 0) {
				anal->bits = hint->bits;
			}
			free (hint);
		}

		if ((oplen = analop (anal, op, at + idx, data + idx, size - idx, R_ANAL_OP_MASK_BASIC)) < 1) {
			break;
		}
		if (op->ptr != UT64_MAX || op->jump != UT64_MAX) {
			switch (oplen) {
			case 2:
				memcpy (ret + idx, "\xf0\x00", 2);
				break;
			case 4:
				memcpy (ret + idx, "\xff\xf0\x00\x00", 4);
				break;
			}
		}
		idx += oplen;
	}

	anal->bits = obits;
	free (op);

	return ret;
}