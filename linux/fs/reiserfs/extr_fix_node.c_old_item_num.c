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
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 

__attribute__((used)) static inline int old_item_num(int new_num, int affected_item_num, int mode)
{
	if (mode == M_PASTE || mode == M_CUT || new_num < affected_item_num)
		return new_num;

	if (mode == M_INSERT) {

		RFALSE(new_num == 0,
		       "vs-8005: for INSERT mode and item number of inserted item");

		return new_num - 1;
	}

	RFALSE(mode != M_DELETE,
	       "vs-8010: old_item_num: mode must be M_DELETE (mode = \'%c\'",
	       mode);
	/* delete mode */
	return new_num + 1;
}