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
struct TYPE_3__ {char* sym; int percpu_absolute; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_range ; 
 scalar_t__ symbol_in_range (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* table ; 
 unsigned int table_cnt ; 

__attribute__((used)) static void make_percpus_absolute(void)
{
	unsigned int i;

	for (i = 0; i < table_cnt; i++)
		if (symbol_in_range(&table[i], &percpu_range, 1)) {
			/*
			 * Keep the 'A' override for percpu symbols to
			 * ensure consistent behavior compared to older
			 * versions of this tool.
			 */
			table[i].sym[0] = 'A';
			table[i].percpu_absolute = 1;
		}
}