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
 int M_CUT ; 
 int M_DELETE ; 
 int M_INSERT ; 
 int M_PASTE ; 
 int /*<<< orphan*/  RFALSE (int,char*,int) ; 

__attribute__((used)) static inline int old_entry_num(int is_affected, int virtual_entry_num,
				int pos_in_item, int mode)
{
	if (mode == M_INSERT || mode == M_DELETE)
		return virtual_entry_num;

	if (!is_affected)
		/* cut or paste is applied to another item */
		return virtual_entry_num;

	if (virtual_entry_num < pos_in_item)
		return virtual_entry_num;

	if (mode == M_CUT)
		return virtual_entry_num + 1;

	RFALSE(mode != M_PASTE || virtual_entry_num == 0,
	       "vs-8015: old_entry_num: mode must be M_PASTE (mode = \'%c\'",
	       mode);

	return virtual_entry_num - 1;
}