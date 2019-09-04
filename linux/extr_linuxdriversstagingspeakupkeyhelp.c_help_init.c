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
 int MSG_FUNCNAMES_END ; 
 int MSG_FUNCNAMES_START ; 
 scalar_t__ SHIFT_TBL_SIZE ; 
 char SPACE ; 
 int* letter_offsets ; 
 char* spk_msg_get (int) ; 
 scalar_t__* spk_our_keys ; 
 scalar_t__ state_tbl ; 

__attribute__((used)) static int help_init(void)
{
	char start = SPACE;
	int i;
	int num_funcs = MSG_FUNCNAMES_END - MSG_FUNCNAMES_START + 1;

	state_tbl = spk_our_keys[0] + SHIFT_TBL_SIZE + 2;
	for (i = 0; i < num_funcs; i++) {
		char *cur_funcname = spk_msg_get(MSG_FUNCNAMES_START + i);

		if (start == *cur_funcname)
			continue;
		start = *cur_funcname;
		letter_offsets[(start & 31) - 1] = i;
	}
	return 0;
}