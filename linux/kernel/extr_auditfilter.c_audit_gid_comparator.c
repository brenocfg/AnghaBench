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
typedef  int u32 ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
#define  Audit_bitmask 135 
#define  Audit_bittest 134 
#define  Audit_equal 133 
#define  Audit_ge 132 
#define  Audit_gt 131 
#define  Audit_le 130 
#define  Audit_lt 129 
#define  Audit_not_equal 128 
 int gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gid_gte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gid_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gid_lte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int audit_gid_comparator(kgid_t left, u32 op, kgid_t right)
{
	switch (op) {
	case Audit_equal:
		return gid_eq(left, right);
	case Audit_not_equal:
		return !gid_eq(left, right);
	case Audit_lt:
		return gid_lt(left, right);
	case Audit_le:
		return gid_lte(left, right);
	case Audit_gt:
		return gid_gt(left, right);
	case Audit_ge:
		return gid_gte(left, right);
	case Audit_bitmask:
	case Audit_bittest:
	default:
		return 0;
	}
}