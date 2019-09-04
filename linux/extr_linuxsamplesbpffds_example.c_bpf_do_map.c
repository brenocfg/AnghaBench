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

/* Variables and functions */
 int BPF_F_KEY ; 
 int BPF_F_KEY_VAL ; 
 int BPF_F_PIN ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_map_create () ; 
 int bpf_map_lookup_elem (int,int*,int*) ; 
 int bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 int bpf_obj_get (char const*) ; 
 int bpf_obj_pin (int,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_do_map(const char *file, uint32_t flags, uint32_t key,
		      uint32_t value)
{
	int fd, ret;

	if (flags & BPF_F_PIN) {
		fd = bpf_map_create();
		printf("bpf: map fd:%d (%s)\n", fd, strerror(errno));
		assert(fd > 0);

		ret = bpf_obj_pin(fd, file);
		printf("bpf: pin ret:(%d,%s)\n", ret, strerror(errno));
		assert(ret == 0);
	} else {
		fd = bpf_obj_get(file);
		printf("bpf: get fd:%d (%s)\n", fd, strerror(errno));
		assert(fd > 0);
	}

	if ((flags & BPF_F_KEY_VAL) == BPF_F_KEY_VAL) {
		ret = bpf_map_update_elem(fd, &key, &value, 0);
		printf("bpf: fd:%d u->(%u:%u) ret:(%d,%s)\n", fd, key, value,
		       ret, strerror(errno));
		assert(ret == 0);
	} else if (flags & BPF_F_KEY) {
		ret = bpf_map_lookup_elem(fd, &key, &value);
		printf("bpf: fd:%d l->(%u):%u ret:(%d,%s)\n", fd, key, value,
		       ret, strerror(errno));
		assert(ret == 0);
	}

	return 0;
}