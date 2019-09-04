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
struct bpf_prog_info {int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_TAG_SIZE ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 int bpf_prog_get_fd_by_id (unsigned int) ; 
 int bpf_prog_get_next_id (unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,unsigned int,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prog_fd_by_tag(unsigned char *tag)
{
	unsigned int id = 0;
	int err;
	int fd;

	while (true) {
		struct bpf_prog_info info = {};
		__u32 len = sizeof(info);

		err = bpf_prog_get_next_id(id, &id);
		if (err) {
			p_err("%s", strerror(errno));
			return -1;
		}

		fd = bpf_prog_get_fd_by_id(id);
		if (fd < 0) {
			p_err("can't get prog by id (%u): %s",
			      id, strerror(errno));
			return -1;
		}

		err = bpf_obj_get_info_by_fd(fd, &info, &len);
		if (err) {
			p_err("can't get prog info (%u): %s",
			      id, strerror(errno));
			close(fd);
			return -1;
		}

		if (!memcmp(tag, info.tag, BPF_TAG_SIZE))
			return fd;

		close(fd);
	}
}