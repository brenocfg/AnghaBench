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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct addrinfo_data {int /*<<< orphan*/  sockaddr_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int inet_aton (char const*,int /*<<< orphan*/ *) ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  looks_like_numeric_ipv6 (char const*) ; 

__attribute__((used)) static int my_inet_aton(const char *node, struct addrinfo_data* space)
{
	int ret;
	((struct sockaddr_in *) &space->sockaddr_space)->sin_family = AF_INET;
	ret = inet_aton(node, &((struct sockaddr_in *) &space->sockaddr_space)->sin_addr);
	if(ret || !looks_like_numeric_ipv6(node)) return ret;
	ret = inet_pton(AF_INET6, node, &((struct sockaddr_in6 *) &space->sockaddr_space)->sin6_addr);
	if(ret) ((struct sockaddr_in6 *) &space->sockaddr_space)->sin6_family = AF_INET6;
	return ret;
}