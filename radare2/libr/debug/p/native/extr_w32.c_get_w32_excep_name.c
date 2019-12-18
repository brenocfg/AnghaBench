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

/* Variables and functions */
#define  EXCEPTION_ACCESS_VIOLATION 132 
#define  EXCEPTION_ARRAY_BOUNDS_EXCEEDED 131 
#define  EXCEPTION_ILLEGAL_INSTRUCTION 130 
#define  EXCEPTION_INT_DIVIDE_BY_ZERO 129 
#define  EXCEPTION_STACK_OVERFLOW 128 

__attribute__((used)) static char *get_w32_excep_name(unsigned long code) {
	char *desc;
	switch (code) {
	/* fatal exceptions */
	case EXCEPTION_ACCESS_VIOLATION:
		desc = "access violation";
		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		desc = "array bounds exceeded";
		break;
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		desc = "illegal instruction";
		break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		desc = "divide by zero";
		break;
	case EXCEPTION_STACK_OVERFLOW:
		desc = "stack overflow";
		break;
	default:
		desc = "unknown";
	}

	return desc;
}