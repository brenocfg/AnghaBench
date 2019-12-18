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
struct btf {int dummy; } ;
struct bpf_btf_info {int btf_size; void* btf; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  btf_info ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btf*) ; 
 int PTR_ERR (struct btf*) ; 
 int bpf_btf_get_fd_by_id (int) ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_btf_info*,int*) ; 
 struct btf* btf__new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* ptr_to_u64 (void*) ; 
 void* realloc (void*,int) ; 

int btf__get_from_id(__u32 id, struct btf **btf)
{
	struct bpf_btf_info btf_info = { 0 };
	__u32 len = sizeof(btf_info);
	__u32 last_size;
	int btf_fd;
	void *ptr;
	int err;

	err = 0;
	*btf = NULL;
	btf_fd = bpf_btf_get_fd_by_id(id);
	if (btf_fd < 0)
		return 0;

	/* we won't know btf_size until we call bpf_obj_get_info_by_fd(). so
	 * let's start with a sane default - 4KiB here - and resize it only if
	 * bpf_obj_get_info_by_fd() needs a bigger buffer.
	 */
	btf_info.btf_size = 4096;
	last_size = btf_info.btf_size;
	ptr = malloc(last_size);
	if (!ptr) {
		err = -ENOMEM;
		goto exit_free;
	}

	memset(ptr, 0, last_size);
	btf_info.btf = ptr_to_u64(ptr);
	err = bpf_obj_get_info_by_fd(btf_fd, &btf_info, &len);

	if (!err && btf_info.btf_size > last_size) {
		void *temp_ptr;

		last_size = btf_info.btf_size;
		temp_ptr = realloc(ptr, last_size);
		if (!temp_ptr) {
			err = -ENOMEM;
			goto exit_free;
		}
		ptr = temp_ptr;
		memset(ptr, 0, last_size);
		btf_info.btf = ptr_to_u64(ptr);
		err = bpf_obj_get_info_by_fd(btf_fd, &btf_info, &len);
	}

	if (err || btf_info.btf_size > last_size) {
		err = errno;
		goto exit_free;
	}

	*btf = btf__new((__u8 *)(long)btf_info.btf, btf_info.btf_size);
	if (IS_ERR(*btf)) {
		err = PTR_ERR(*btf);
		*btf = NULL;
	}

exit_free:
	close(btf_fd);
	free(ptr);

	return err;
}