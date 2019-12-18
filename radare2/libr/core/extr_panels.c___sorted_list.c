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
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  cmpstr ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * r_list_new () ; 
 int /*<<< orphan*/  r_list_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

RList *__sorted_list(RCore *core, char *menu[], int count) {
	RList *list = r_list_new ();
	int i;
	for (i = 0; i < count; i++) {
		if (menu[i]) {
			(void)r_list_append (list, menu[i]);
		}
	}
	r_list_sort (list, cmpstr);
	return list;
}