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
typedef  int DWORD ;

/* Variables and functions */
#define  EXCEPTION_ACCESS_VIOLATION 132 
#define  EXCEPTION_ARRAY_BOUNDS_EXCEEDED 131 
#define  EXCEPTION_ILLEGAL_INSTRUCTION 130 
#define  EXCEPTION_INT_DIVIDE_BY_ZERO 129 
#define  EXCEPTION_STACK_OVERFLOW 128 

__attribute__((used)) static const char *__get_w32_excep_name(DWORD code) {
	switch (code) {
	/* fatal exceptions */
	case EXCEPTION_ACCESS_VIOLATION:
		return "access violation";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		return "array bounds exceeded";
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		return "illegal instruction";
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		return "divide by zero";
	case EXCEPTION_STACK_OVERFLOW:
		return "stack overflow";
	default:
		return "unknown";
	}
}