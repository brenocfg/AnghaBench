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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int BPF_F_PIN ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ATTACH_BPF ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_obj_get (char const*) ; 
 int bpf_obj_pin (int,char const*) ; 
 int bpf_prog_create (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int open_raw_sock (char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_do_prog(const char *file, uint32_t flags, const char *object)
{
	int fd, sock, ret;

	if (flags & BPF_F_PIN) {
		fd = bpf_prog_create(object);
		printf("bpf: prog fd:%d (%s)\n", fd, strerror(errno));
		assert(fd > 0);

		ret = bpf_obj_pin(fd, file);
		printf("bpf: pin ret:(%d,%s)\n", ret, strerror(errno));
		assert(ret == 0);
	} else {
		fd = bpf_obj_get(file);
		printf("bpf: get fd:%d (%s)\n", fd, strerror(errno));
		assert(fd > 0);
	}

	sock = open_raw_sock("lo");
	assert(sock > 0);

	ret = setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &fd, sizeof(fd));
	printf("bpf: sock:%d <- fd:%d attached ret:(%d,%s)\n", sock, fd,
	       ret, strerror(errno));
	assert(ret == 0);

	return 0;
}