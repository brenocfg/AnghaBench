#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EINVAL ; 
 scalar_t__ in4_pton (char const*,size_t,int /*<<< orphan*/ *,char,char const**) ; 
 scalar_t__ in6_pton (char const*,size_t,int /*<<< orphan*/ *,char,char const**) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ceph_pton(const char *str, size_t len, struct sockaddr_storage *ss,
		char delim, const char **ipend)
{
	struct sockaddr_in *in4 = (struct sockaddr_in *) ss;
	struct sockaddr_in6 *in6 = (struct sockaddr_in6 *) ss;

	memset(ss, 0, sizeof(*ss));

	if (in4_pton(str, len, (u8 *)&in4->sin_addr.s_addr, delim, ipend)) {
		ss->ss_family = AF_INET;
		return 0;
	}

	if (in6_pton(str, len, (u8 *)&in6->sin6_addr.s6_addr, delim, ipend)) {
		ss->ss_family = AF_INET6;
		return 0;
	}

	return -EINVAL;
}