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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  name; void* data; } ;
typedef  TYPE_1__ RFSFile ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ r_file_slurp_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fs_posix_read(RFSFile *file, ut64 addr, int len) {
	free (file->data);
	file->data = (void*)r_file_slurp_range (file->name, 0, len, NULL);
	return false;
}