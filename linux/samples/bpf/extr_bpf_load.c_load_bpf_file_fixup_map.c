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
typedef  int /*<<< orphan*/  fixup_map_cb ;

/* Variables and functions */
 int do_load_bpf_file (char const*,int /*<<< orphan*/ ) ; 

int load_bpf_file_fixup_map(const char *path, fixup_map_cb fixup_map)
{
	return do_load_bpf_file(path, fixup_map);
}