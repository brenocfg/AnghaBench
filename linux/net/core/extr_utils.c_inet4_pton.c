#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sockaddr_storage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; TYPE_1__ sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EINVAL ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ in4_pton (char const*,int,int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int inet4_pton(const char *src, u16 port_num,
		struct sockaddr_storage *addr)
{
	struct sockaddr_in *addr4 = (struct sockaddr_in *)addr;
	int srclen = strlen(src);

	if (srclen > INET_ADDRSTRLEN)
		return -EINVAL;

	if (in4_pton(src, srclen, (u8 *)&addr4->sin_addr.s_addr,
		     '\n', NULL) == 0)
		return -EINVAL;

	addr4->sin_family = AF_INET;
	addr4->sin_port = htons(port_num);

	return 0;
}