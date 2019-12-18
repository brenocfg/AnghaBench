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
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int IF_NAMESIZE ; 
 scalar_t__ ifindex_to_name_ns (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void print_dev_plain(__u32 ifindex, __u64 ns_dev, __u64 ns_inode)
{
	char name[IF_NAMESIZE];

	if (!ifindex)
		return;

	printf("  offloaded_to ");
	if (ifindex_to_name_ns(ifindex, ns_dev, ns_inode, name))
		printf("%s", name);
	else
		printf("ifindex %u ns_dev %llu ns_ino %llu",
		       ifindex, ns_dev, ns_inode);
}