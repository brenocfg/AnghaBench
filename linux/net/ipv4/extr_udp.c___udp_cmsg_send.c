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
typedef  int /*<<< orphan*/  u16 ;
struct cmsghdr {int cmsg_type; int /*<<< orphan*/  cmsg_len; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 int EINVAL ; 
#define  UDP_SEGMENT 128 

__attribute__((used)) static int __udp_cmsg_send(struct cmsghdr *cmsg, u16 *gso_size)
{
	switch (cmsg->cmsg_type) {
	case UDP_SEGMENT:
		if (cmsg->cmsg_len != CMSG_LEN(sizeof(__u16)))
			return -EINVAL;
		*gso_size = *(__u16 *)CMSG_DATA(cmsg);
		return 0;
	default:
		return -EINVAL;
	}
}