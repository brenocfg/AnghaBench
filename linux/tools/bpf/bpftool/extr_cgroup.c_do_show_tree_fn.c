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
struct stat {int dummy; } ;
struct FTW {int /*<<< orphan*/  level; } ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int FTW_D ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int SHOW_TREE_FN_ERR ; 
 int __MAX_BPF_ATTACH_TYPE ; 
 int /*<<< orphan*/  close (int) ; 
 int count_attached_bpf_progs (int,int) ; 
 scalar_t__ errno ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_end_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_string_field (int /*<<< orphan*/ ,char*,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  show_attached_bpf_progs (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int do_show_tree_fn(const char *fpath, const struct stat *sb,
			   int typeflag, struct FTW *ftw)
{
	enum bpf_attach_type type;
	bool skip = true;
	int cgroup_fd;

	if (typeflag != FTW_D)
		return 0;

	cgroup_fd = open(fpath, O_RDONLY);
	if (cgroup_fd < 0) {
		p_err("can't open cgroup %s: %s", fpath, strerror(errno));
		return SHOW_TREE_FN_ERR;
	}

	for (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) {
		int count = count_attached_bpf_progs(cgroup_fd, type);

		if (count < 0 && errno != EINVAL) {
			p_err("can't query bpf programs attached to %s: %s",
			      fpath, strerror(errno));
			close(cgroup_fd);
			return SHOW_TREE_FN_ERR;
		}
		if (count > 0) {
			skip = false;
			break;
		}
	}

	if (skip) {
		close(cgroup_fd);
		return 0;
	}

	if (json_output) {
		jsonw_start_object(json_wtr);
		jsonw_string_field(json_wtr, "cgroup", fpath);
		jsonw_name(json_wtr, "programs");
		jsonw_start_array(json_wtr);
	} else {
		printf("%s\n", fpath);
	}

	for (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++)
		show_attached_bpf_progs(cgroup_fd, type, ftw->level);

	if (errno == EINVAL)
		/* Last attach type does not support query.
		 * Do not report an error for this, especially because batch
		 * mode would stop processing commands.
		 */
		errno = 0;

	if (json_output) {
		jsonw_end_array(json_wtr);
		jsonw_end_object(json_wtr);
	}

	close(cgroup_fd);

	return 0;
}