#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int btf_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,char*,int,...) ; 
 int bpf_create_map_xattr (TYPE_1__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int load_btf () ; 
 TYPE_1__ xattr ; 

__attribute__((used)) static int create_sk_storage_map(void)
{
	int btf_fd, map_fd;

	btf_fd = load_btf();
	CHECK(btf_fd == -1, "bpf_load_btf", "btf_fd:%d errno:%d\n",
	      btf_fd, errno);
	xattr.btf_fd = btf_fd;

	map_fd = bpf_create_map_xattr(&xattr);
	xattr.btf_fd = -1;
	close(btf_fd);
	CHECK(map_fd == -1,
	      "bpf_create_map_xattr()", "errno:%d\n", errno);

	return map_fd;
}