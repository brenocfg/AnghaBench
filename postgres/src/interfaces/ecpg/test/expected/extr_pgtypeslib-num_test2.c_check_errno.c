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
#define  PGTYPES_NUM_BAD_NUMERIC 131 
#define  PGTYPES_NUM_DIVIDE_ZERO 130 
#define  PGTYPES_NUM_OVERFLOW 129 
#define  PGTYPES_NUM_UNDERFLOW 128 
 int errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int) ; 

__attribute__((used)) static void
check_errno(void)
{
	switch(errno)
	{
		case 0:
			printf("(no errno set) - ");
			break;
		case PGTYPES_NUM_OVERFLOW:
			printf("(errno == PGTYPES_NUM_OVERFLOW) - ");
			break;
		case PGTYPES_NUM_UNDERFLOW:
			printf("(errno == PGTYPES_NUM_UNDERFLOW) - ");
			break;
		case PGTYPES_NUM_BAD_NUMERIC:
			printf("(errno == PGTYPES_NUM_BAD_NUMERIC) - ");
			break;
		case PGTYPES_NUM_DIVIDE_ZERO:
			printf("(errno == PGTYPES_NUM_DIVIDE_ZERO) - ");
			break;
		default:
			printf("(unknown errno (%d))\n", errno);
			printf("(libc: (%s)) ", strerror(errno));
			break;
	}

}