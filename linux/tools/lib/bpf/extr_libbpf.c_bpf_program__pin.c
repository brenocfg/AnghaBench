#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nr; } ;
struct bpf_program {TYPE_1__ instances; int /*<<< orphan*/  section_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int PATH_MAX ; 
 int bpf_program__pin_instance (struct bpf_program*,char const*,int) ; 
 int /*<<< orphan*/  bpf_program__unpin_instance (struct bpf_program*,char*,int) ; 
 int check_path (char const*) ; 
 int make_dir (char const*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/  rmdir (char const*) ; 
 int snprintf (char*,int,char*,char const*,int) ; 

int bpf_program__pin(struct bpf_program *prog, const char *path)
{
	int i, err;

	err = check_path(path);
	if (err)
		return err;

	if (prog == NULL) {
		pr_warning("invalid program pointer\n");
		return -EINVAL;
	}

	if (prog->instances.nr <= 0) {
		pr_warning("no instances of prog %s to pin\n",
			   prog->section_name);
		return -EINVAL;
	}

	if (prog->instances.nr == 1) {
		/* don't create subdirs when pinning single instance */
		return bpf_program__pin_instance(prog, path, 0);
	}

	err = make_dir(path);
	if (err)
		return err;

	for (i = 0; i < prog->instances.nr; i++) {
		char buf[PATH_MAX];
		int len;

		len = snprintf(buf, PATH_MAX, "%s/%d", path, i);
		if (len < 0) {
			err = -EINVAL;
			goto err_unpin;
		} else if (len >= PATH_MAX) {
			err = -ENAMETOOLONG;
			goto err_unpin;
		}

		err = bpf_program__pin_instance(prog, buf, i);
		if (err)
			goto err_unpin;
	}

	return 0;

err_unpin:
	for (i = i - 1; i >= 0; i--) {
		char buf[PATH_MAX];
		int len;

		len = snprintf(buf, PATH_MAX, "%s/%d", path, i);
		if (len < 0)
			continue;
		else if (len >= PATH_MAX)
			continue;

		bpf_program__unpin_instance(prog, buf, i);
	}

	rmdir(path);

	return err;
}