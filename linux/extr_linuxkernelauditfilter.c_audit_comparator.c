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

/* Variables and functions */
#define  Audit_bitmask 135 
#define  Audit_bittest 134 
#define  Audit_equal 133 
#define  Audit_ge 132 
#define  Audit_gt 131 
#define  Audit_le 130 
#define  Audit_lt 129 
#define  Audit_not_equal 128 
 int /*<<< orphan*/  BUG () ; 

int audit_comparator(u32 left, u32 op, u32 right)
{
	switch (op) {
	case Audit_equal:
		return (left == right);
	case Audit_not_equal:
		return (left != right);
	case Audit_lt:
		return (left < right);
	case Audit_le:
		return (left <= right);
	case Audit_gt:
		return (left > right);
	case Audit_ge:
		return (left >= right);
	case Audit_bitmask:
		return (left & right);
	case Audit_bittest:
		return ((left & right) == right);
	default:
		BUG();
		return 0;
	}
}