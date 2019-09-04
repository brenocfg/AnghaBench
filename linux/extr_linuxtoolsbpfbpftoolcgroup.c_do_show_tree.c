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
 int /*<<< orphan*/  FTW_MOUNT ; 
#define  NFTW_ERR 129 
#define  SHOW_TREE_FN_ERR 128 
 int /*<<< orphan*/  do_show_tree_fn ; 
 int /*<<< orphan*/  errno ; 
 char* find_cgroup_root () ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int nftw (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_show_tree(int argc, char **argv)
{
	char *cgroup_root;
	int ret;

	switch (argc) {
	case 0:
		cgroup_root = find_cgroup_root();
		if (!cgroup_root) {
			p_err("cgroup v2 isn't mounted");
			return -1;
		}
		break;
	case 1:
		cgroup_root = argv[0];
		break;
	default:
		p_err("too many parameters for cgroup tree");
		return -1;
	}


	if (json_output)
		jsonw_start_array(json_wtr);
	else
		printf("%s\n"
		       "%-8s %-15s %-15s %-15s\n",
		       "CgroupPath",
		       "ID", "AttachType", "AttachFlags", "Name");

	switch (nftw(cgroup_root, do_show_tree_fn, 1024, FTW_MOUNT)) {
	case NFTW_ERR:
		p_err("can't iterate over %s: %s", cgroup_root,
		      strerror(errno));
		ret = -1;
		break;
	case SHOW_TREE_FN_ERR:
		ret = -1;
		break;
	default:
		ret = 0;
	}

	if (json_output)
		jsonw_end_array(json_wtr);

	if (argc == 0)
		free(cgroup_root);

	return ret;
}