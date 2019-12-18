#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int type; int time; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RFSFile ;

/* Variables and functions */
 TYPE_1__* r_fs_file_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void append_file(RList *list, const char *name, int type, int time, ut64 size) {
	RFSFile *fsf = r_fs_file_new (NULL, name);
	if (!fsf) {
		return;
	}
	fsf->type = type;
	fsf->time = time;
	fsf->size = size;
	r_list_append (list, fsf);
}