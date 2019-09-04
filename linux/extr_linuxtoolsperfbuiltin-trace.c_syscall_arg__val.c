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
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
struct syscall_arg {unsigned char* args; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned long*,unsigned char*,int) ; 

unsigned long syscall_arg__val(struct syscall_arg *arg, u8 idx)
{
	unsigned long val;
	unsigned char *p = arg->args + sizeof(unsigned long) * idx;

	memcpy(&val, p, sizeof(val));
	return val;
}