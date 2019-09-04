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
struct in_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int inet_pton (int /*<<< orphan*/ ,char*,struct in_addr*) ; 

__attribute__((used)) static int is_ipv4(char *addr)
{
	int ret;
	struct in_addr ipv4_addr;

	ret = inet_pton(AF_INET, addr, &ipv4_addr);

	if (ret == 1)
		return 1;
	return 0;
}