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
 int FTW_ACTIONRETVAL ; 
 int FTW_PHYS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  has_perf_query_support () ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int nftw (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_proc ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_show(int argc, char **argv)
{
	int flags = FTW_ACTIONRETVAL | FTW_PHYS;
	int err = 0, nopenfd = 16;

	if (!has_perf_query_support())
		return -1;

	if (json_output)
		jsonw_start_array(json_wtr);
	if (nftw("/proc", show_proc, nopenfd, flags) == -1) {
		p_err("%s", strerror(errno));
		err = -1;
	}
	if (json_output)
		jsonw_end_array(json_wtr);

	return err;
}