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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_DEVMAP_HASH ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_devmap_hash(unsigned int task, void *data)
{
	int fd;
	__u32 key, value;

	fd = bpf_create_map(BPF_MAP_TYPE_DEVMAP_HASH, sizeof(key), sizeof(value),
			    2, 0);
	if (fd < 0) {
		printf("Failed to create devmap_hash '%s'!\n", strerror(errno));
		exit(1);
	}

	close(fd);
}