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
struct btf {int fd; int /*<<< orphan*/  data_size; void* data; } ;
typedef  int /*<<< orphan*/  btf_print_fn_t ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LOG_BUF_SIZE ; 
 int ENOMEM ; 
 struct btf* ERR_PTR (int) ; 
 int bpf_load_btf (void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btf__free (struct btf*) ; 
 int btf_parse_hdr (struct btf*,int /*<<< orphan*/ ) ; 
 int btf_parse_str_sec (struct btf*,int /*<<< orphan*/ ) ; 
 int btf_parse_type_sec (struct btf*,int /*<<< orphan*/ ) ; 
 struct btf* calloc (int,int) ; 
 int /*<<< orphan*/  elog (char*,char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

struct btf *btf__new(__u8 *data, __u32 size, btf_print_fn_t err_log)
{
	__u32 log_buf_size = 0;
	char *log_buf = NULL;
	struct btf *btf;
	int err;

	btf = calloc(1, sizeof(struct btf));
	if (!btf)
		return ERR_PTR(-ENOMEM);

	btf->fd = -1;

	if (err_log) {
		log_buf = malloc(BPF_LOG_BUF_SIZE);
		if (!log_buf) {
			err = -ENOMEM;
			goto done;
		}
		*log_buf = 0;
		log_buf_size = BPF_LOG_BUF_SIZE;
	}

	btf->data = malloc(size);
	if (!btf->data) {
		err = -ENOMEM;
		goto done;
	}

	memcpy(btf->data, data, size);
	btf->data_size = size;

	btf->fd = bpf_load_btf(btf->data, btf->data_size,
			       log_buf, log_buf_size, false);

	if (btf->fd == -1) {
		err = -errno;
		elog("Error loading BTF: %s(%d)\n", strerror(errno), errno);
		if (log_buf && *log_buf)
			elog("%s\n", log_buf);
		goto done;
	}

	err = btf_parse_hdr(btf, err_log);
	if (err)
		goto done;

	err = btf_parse_str_sec(btf, err_log);
	if (err)
		goto done;

	err = btf_parse_type_sec(btf, err_log);

done:
	free(log_buf);

	if (err) {
		btf__free(btf);
		return ERR_PTR(err);
	}

	return btf;
}