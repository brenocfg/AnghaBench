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
 int /*<<< orphan*/  bpf_map_get_fd_by_id ; 
 int do_pin_any (int,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_pin(int argc, char **argv)
{
	int err;

	err = do_pin_any(argc, argv, bpf_map_get_fd_by_id);
	if (!err && json_output)
		jsonw_null(json_wtr);
	return err;
}