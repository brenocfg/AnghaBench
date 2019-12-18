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
 int BAD_ARG () ; 
 int /*<<< orphan*/  REQ_ARGS (int) ; 
 int bpf_map_freeze (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_null (int /*<<< orphan*/ ) ; 
 int map_parse_fd (int*,char***) ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_freeze(int argc, char **argv)
{
	int err, fd;

	if (!REQ_ARGS(2))
		return -1;

	fd = map_parse_fd(&argc, &argv);
	if (fd < 0)
		return -1;

	if (argc) {
		close(fd);
		return BAD_ARG();
	}

	err = bpf_map_freeze(fd);
	close(fd);
	if (err) {
		p_err("failed to freeze map: %s", strerror(errno));
		return err;
	}

	if (json_output)
		jsonw_null(json_wtr);

	return 0;
}