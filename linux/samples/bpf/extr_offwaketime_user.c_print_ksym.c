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
struct ksym {char* name; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 scalar_t__ PRINT_RAW_ADDR ; 
 struct ksym* ksym_search (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_ksym(__u64 addr)
{
	struct ksym *sym;

	if (!addr)
		return;
	sym = ksym_search(addr);
	if (!sym) {
		printf("ksym not found. Is kallsyms loaded?\n");
		return;
	}

	if (PRINT_RAW_ADDR)
		printf("%s/%llx;", sym->name, addr);
	else
		printf("%s;", sym->name);
}