#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int len; unsigned int* sym; } ;

/* Variables and functions */
 unsigned int** best_table ; 
 int* best_table_len ; 
 TYPE_1__* table ; 
 unsigned int table_cnt ; 

__attribute__((used)) static void insert_real_symbols_in_table(void)
{
	unsigned int i, j, c;

	for (i = 0; i < table_cnt; i++) {
		for (j = 0; j < table[i].len; j++) {
			c = table[i].sym[j];
			best_table[c][0]=c;
			best_table_len[c]=1;
		}
	}
}