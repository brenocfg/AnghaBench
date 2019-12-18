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
typedef  char* u64 ;
struct trace_entry {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* trace_decode_reg (char*) ; 

__attribute__((used)) static void trace_print_reg(struct trace_entry *e)
{
	u64 *p, *reg, *value;
	char *name;

	p = (u64 *)e->data;
	reg = p++;
	value = p;

	name = trace_decode_reg(*reg);
	if (name)
		printf("register %-10s = 0x%016llx\n", name, *value);
	else
		printf("register %lld = 0x%016llx\n", *reg, *value);
}