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
struct sockaddr_storage {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int ceph_dns_resolve_name(const char *name, size_t namelen,
		struct sockaddr_storage *ss, char delim, const char **ipend)
{
	return -EINVAL;
}