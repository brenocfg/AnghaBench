#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ne_header; } ;
typedef  TYPE_2__ r_bin_ne_obj_t ;
struct TYPE_4__ {int targOS; } ;

/* Variables and functions */

__attribute__((used)) static char *__get_target_os(r_bin_ne_obj_t *bin) {
	switch (bin->ne_header->targOS) {
	case 1:
		return "OS/2";
	case 2:
		return "Windows";
	case 3:
		return "European MS-DOS 4.x";
	case 4:
		return "Windows 386";
	case 5:
		return "BOSS (Borland Operating System Services)";
	default:
		return "Unknown";
	}
}