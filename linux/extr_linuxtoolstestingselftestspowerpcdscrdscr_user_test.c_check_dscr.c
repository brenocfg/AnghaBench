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
 unsigned long get_dscr () ; 
 unsigned long get_dscr_usr () ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int check_dscr(char *str)
{
	unsigned long cur_dscr, cur_dscr_usr;

	cur_dscr = get_dscr();
	cur_dscr_usr = get_dscr_usr();
	if (cur_dscr != cur_dscr_usr) {
		printf("%s set, kernel get %lx != user get %lx\n",
					str, cur_dscr, cur_dscr_usr);
		return 1;
	}
	return 0;
}