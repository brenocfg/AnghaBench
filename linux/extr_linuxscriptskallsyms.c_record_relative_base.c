#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long long addr; } ;

/* Variables and functions */
 unsigned long long relative_base ; 
 int /*<<< orphan*/  symbol_absolute (TYPE_1__*) ; 
 TYPE_1__* table ; 
 unsigned int table_cnt ; 

__attribute__((used)) static void record_relative_base(void)
{
	unsigned int i;

	relative_base = -1ULL;
	for (i = 0; i < table_cnt; i++)
		if (!symbol_absolute(&table[i]) &&
		    table[i].addr < relative_base)
			relative_base = table[i].addr;
}