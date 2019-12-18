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
struct TYPE_2__ {scalar_t__ path; scalar_t__ dir; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RFSRoot ;

/* Variables and functions */
 int /*<<< orphan*/  append_file (int /*<<< orphan*/ *,scalar_t__,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ *) ; 
 TYPE_1__* routes ; 

__attribute__((used)) static RList *__root(RFSRoot *root, const char *path) {
	RList *list = r_list_newf (NULL);
	if (!list) {
		return NULL;
	}
	int i;
	for (i = 0; routes[i].path; i++) {
		char type = routes[i].dir? 'd': 'f';
		append_file (list, routes[i].path + 1, type, 0, 0);
	}
	return list;
}