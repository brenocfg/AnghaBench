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
typedef  int /*<<< orphan*/  RFSPartition ;

/* Variables and functions */
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fs_parhook(void* disk, void* ptr, void* closure) {
	RFSPartition* par = ptr;
	RList* list = (RList*) closure;
	r_list_append (list, par);
	return 0;
}