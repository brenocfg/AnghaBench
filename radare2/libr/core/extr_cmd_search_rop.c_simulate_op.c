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
typedef  scalar_t__ ut64 ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool simulate_op (const char *op, ut64 src1, ut64 src2, ut64 old_src1, ut64 old_src2, ut64 *result, int size) {
	ut64 limit;
	if (size == 64) {
		limit = UT64_MAX;
	} else {
		limit = 1ULL << size;
	}

	if (!strcmp (op, "^")) {
		*result =  src1 ^ src2;
		return true;
	}
	if (!strcmp (op, "+")) {
		*result = src1 + src2;
		return true;
	}
	if (!strcmp (op, "-")) {
		if (src2 > src1) {
			*result = limit + (src1 - src2);
		} else {
			*result = src1 - src2;
		}
		return true;
	}
	if (!strcmp (op, "*")) {
		*result = src1 * src2;
		return true;
	}
	if (!strcmp (op, "|")) {
		*result = src1 | src2;
		return true;
	}
	if (!strcmp (op, "/")) {
		*result = src1 / src2;
		return true;
	}
	if (!strcmp (op, "%")) {
		*result = src1 % src2;
		return true;
	}
	if (!strcmp (op, "<<")) {
		*result = src1 << src2;
		return true;
	}
	if (!strcmp (op, ">>")) {
		*result = src1 >> src2;
		return true;
	}
	if (!strcmp (op, "&")) {
		*result = src1 & src2;
		return true;
	}
	if (!strcmp (op, "+=")) {
		*result = old_src1 + src2;
		return true;
	}
	if (!strcmp (op, "-=")) {
		if (src2 > old_src1) {
			*result = limit + (old_src1 - src2);
		} else {
			*result = old_src1 - src2;
		}
		return true;
	}
	if (!strcmp (op, "*=")) {
		*result = old_src1 * src2;
		return true;
	}
	if (!strcmp (op, "/=")) {
		*result = old_src1 / src2;
		return true;
	}
	if (!strcmp (op, "%=")) {
		*result = old_src1 % src2;
		return true;
	}
	if (!strcmp (op, "<<")) {
		*result = src1 << src2;
		return true;
	}
	if (!strcmp (op, ">>")) {
		*result = src1 >> src2;
		return true;
	}
	if (!strcmp (op, "&=")) {
		*result = src1 & src2;
		return true;
	}
	if (!strcmp (op, "^=")) {
		*result = src1 ^ src2;
		return true;
	}
	if (!strcmp (op, "|=")) {
		*result = src1 | src2;
		return true;
	}
	return false;
}