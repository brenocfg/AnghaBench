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
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
#define  E_AND 137 
#define  E_EQUAL 136 
#define  E_GEQ 135 
#define  E_GTH 134 
#define  E_LEQ 133 
#define  E_LIST 132 
#define  E_LTH 131 
#define  E_NOT 130 
#define  E_OR 129 
#define  E_UNEQUAL 128 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int expr_compare_type(enum expr_type t1, enum expr_type t2)
{
	if (t1 == t2)
		return 0;
	switch (t1) {
	case E_LEQ:
	case E_LTH:
	case E_GEQ:
	case E_GTH:
		if (t2 == E_EQUAL || t2 == E_UNEQUAL)
			return 1;
	case E_EQUAL:
	case E_UNEQUAL:
		if (t2 == E_NOT)
			return 1;
	case E_NOT:
		if (t2 == E_AND)
			return 1;
	case E_AND:
		if (t2 == E_OR)
			return 1;
	case E_OR:
		if (t2 == E_LIST)
			return 1;
	case E_LIST:
		if (t2 == 0)
			return 1;
	default:
		return -1;
	}
	printf("[%dgt%d?]", t1, t2);
	return 0;
}