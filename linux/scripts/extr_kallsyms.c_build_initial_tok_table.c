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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  sym; } ;

/* Variables and functions */
 int /*<<< orphan*/  learn_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ symbol_valid (TYPE_1__*) ; 
 TYPE_1__* table ; 
 unsigned int table_cnt ; 

__attribute__((used)) static void build_initial_tok_table(void)
{
	unsigned int i, pos;

	pos = 0;
	for (i = 0; i < table_cnt; i++) {
		if ( symbol_valid(&table[i]) ) {
			if (pos != i)
				table[pos] = table[i];
			learn_symbol(table[pos].sym, table[pos].len);
			pos++;
		}
	}
	table_cnt = pos;
}