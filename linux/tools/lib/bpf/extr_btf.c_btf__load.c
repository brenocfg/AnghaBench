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
struct btf {int /*<<< orphan*/  fd; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LOG_BUF_SIZE ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bpf_load_btf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,char*,...) ; 
 int /*<<< orphan*/  strerror (int) ; 

int btf__load(struct btf *btf)
{
	__u32 log_buf_size = BPF_LOG_BUF_SIZE;
	char *log_buf = NULL;
	int err = 0;

	if (btf->fd >= 0)
		return -EEXIST;

	log_buf = malloc(log_buf_size);
	if (!log_buf)
		return -ENOMEM;

	*log_buf = 0;

	btf->fd = bpf_load_btf(btf->data, btf->data_size,
			       log_buf, log_buf_size, false);
	if (btf->fd < 0) {
		err = -errno;
		pr_warning("Error loading BTF: %s(%d)\n", strerror(errno), errno);
		if (*log_buf)
			pr_warning("%s\n", log_buf);
		goto done;
	}

done:
	free(log_buf);
	return err;
}