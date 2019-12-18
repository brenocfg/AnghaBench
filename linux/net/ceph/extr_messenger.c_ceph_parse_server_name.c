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
struct ceph_entity_addr {int dummy; } ;

/* Variables and functions */
 int ceph_dns_resolve_name (char const*,size_t,struct ceph_entity_addr*,char,char const**) ; 
 int ceph_pton (char const*,size_t,struct ceph_entity_addr*,char,char const**) ; 

__attribute__((used)) static int ceph_parse_server_name(const char *name, size_t namelen,
		struct ceph_entity_addr *addr, char delim, const char **ipend)
{
	int ret;

	ret = ceph_pton(name, namelen, addr, delim, ipend);
	if (ret)
		ret = ceph_dns_resolve_name(name, namelen, addr, delim, ipend);

	return ret;
}